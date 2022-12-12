
unsigned long final_counts;
unsigned long start_time;
unsigned long measured_time;
unsigned long tiempo_med;
unsigned long max_tiempo_med = 10*1000000; //Tiempo entre actualizaciones de 10 segundos.
unsigned long tiempo_histo = 10; // ancho histograma en microsegundos
const byte PinLectura = 5; //Button to perform interrupt
const byte PinEventos = 2; //Pin en donde se genera el evento
const int max_elementos = 740;
unsigned int Tabla[max_elementos];
unsigned long actual =  0;

void setup() {
  // put your setup code here, to run once:
  pinMode(PinEventos,INPUT);
  attachInterrupt(digitalPinToInterrupt(PinEventos), button_ISR, RISING);
  Serial.begin(115200);
  InicializarModoB();
}

void loop() {
  // put your main code here, to run repeatedly:
  start_time = micros();
  delay(10000);
  int i = 0;
  Serial.println();
  Serial.println("Inicio Tabla:");
  for(i=0; i<max_elementos; i++){
    Serial.println(Tabla[i]);
    //Serial.print("; ");
  }
  // reinicio el proceso de medicion
  for(i=0; i<max_elementos; i++){
    Tabla[i] = 0;
  }

}

void button_ISR(){
  actual = micros();
  measured_time = actual - start_time;
  int Pos = 0;
  Pos = (int) measured_time/tiempo_histo;
  if (Pos > max_elementos){
    Pos = max_elementos;
  }
  Tabla[Pos] = Tabla[Pos] +1;
  start_time = actual;
}


void InicializarModoB(){
  int i = 0;
  for(i=0; i<max_elementos; i++){
    Tabla[i] = 0;
  }; 
}
