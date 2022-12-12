unsigned int dwell = 20000; // dwell in microseconds for counter
unsigned long final_counts;
unsigned long start_time;
unsigned long measured_time;
float salida;

//frequency counter using Timer1 counter without overflow count
//TCNT1 16 bit max value = 65,534
//20ms sample period gives frequency counter to a bit over 32 mhz

void setup() {
	// put your setup code here, to run once:
	//INICIALIZACIÓN SERIE
	Serial.begin(115200);

	TCCR1A = 0; //initialize Timer1
	TCCR1B = 0;
	TCNT1 = 0;
	pinMode(5,INPUT);
}

void loop() {
	// put your main code here, to run repeatedly:
	start_time = micros();
   
	// External clock source on Timer1, pin (D5). Clock on rising edge.
	// Setting bits starts timer
	TCCR1B =  bit (CS10) | bit (CS11) | bit (CS12); //external clock source pin D5 rising edge
	bitClear(TCCR1B, 7);
	bitClear(TCCR1B, 6);
	TCNT1 = 0;//Inicializo el registro en donde se cuentan los fotones
	while (micros() - start_time < dwell) {} // do nothing but wait and count during dwell time

	TCCR1B = 0; //detengo el conteo
	final_counts = TCNT1; //frequency limited by unsigned int TCNT1 without rollover counts

	measured_time = micros() - start_time;

	salida = (float)final_counts/1;
	Serial.println( salida, 0); //20ms sample in Hz
}
