#include <avr/io.h>
#include <avr/interrupt.h>	//import bibliotek z toolchaina

#include "ir.h"
#include "../makra.h"		//import pozosta³ych plików programu

volatile uint8_t IR_flaga;		//flaga informuj¹ca ¿e zosta³y odebrane dane

//odebrane wartoœci z pilota
volatile uint8_t IR_adres;		//adres urz¹dzenia
volatile uint8_t IR_komenda;	//komenda z urz¹denia
volatile uint8_t IR_toggle;		//znak toggle

volatile uint8_t irCnt;			//licznik odebranych bitów

//inicjalizacja peryferiow odbierania danch przez RC5
void ir_init()
{
	DDR(IR_PORT) &= ~IR_IN;		// pin jako wejœcie
	PORT(IR_PORT) |= IR_IN;		// podci¹gniêcie pinu do VCC
	#if TIMER1_PRESCALER == 1
		TCCR1B |= (1<<CS10);         	//prescaler 1
	#endif
	#if TIMER1_PRESCALER == 8
		TCCR1B |= (1<<CS11);         	//prescaler 8
	#endif
	#if TIMER1_PRESCALER == 64
	  	TCCR1B |= (1<<CS11)|(1<<CS10); //prescaler 64
	#endif
	#if TIMER1_PRESCALER == 256
		TCCR1B |= (1<<CS12);         	//prescaler 256
	#endif

	TCCR1B &= ~(1<<ICES1);      	//ICR zbocze opadaj¹ce
	irCnt = 0;						//licznik wystapien zboczy

	TIMSK |= (1<<TICIE1);        	//wlaczenie przerwan od ICR
	IR_flaga = 0;					//flaga, czy dane odebrano
}



// procedura obs³ugi przerwania ICR1
ISR(TIMER1_CAPT_vect)
{
	//makra okreslaj¹ce status odebranej ramki danych
	#define IR_RESTART 0
	#define IR_OK 1
	#define IR_KONIEC 2
	#define IR_BLAD 3

	//zmienne dotyczace dlogosci impulsu, wartosci i statusu ramki
	static uint16_t ostatniaWar;
	uint16_t szerokoscIr;
	static uint8_t IrSzerCnt;
	static uint16_t odebranaIr;
	static uint8_t statusIr;

	//szerokosc impulsu, obliczenie
	szerokoscIr = ICR1 - ostatniaWar;
	ostatniaWar = ICR1;

	TCCR1B ^= (1<<ICES1);	//zmiana zbocza wyzwalaj¹cego przerwanie ICR

	if (szerokoscIr > MAX_BIT) irCnt = 0;	//blednie odczytany bit, zerowanie licznika

	if (irCnt > 0) statusIr = IR_OK;	//licznik wiekszy od zero => OK

	if (irCnt == 0) 	//pomyslnie odebrana ramka danych
	{
		TCCR1B |= (1<<ICES1);
		IrSzerCnt = 0;
		odebranaIr = 0;
		irCnt++;
		statusIr = IR_KONIEC;
	}

	//jesli status jest gotowy do odbioru danych ...
	if (statusIr == IR_OK)
	{
		// restart odbioru jeœli czas na jeden pol bit jest zbyt krotki
		if(szerokoscIr < MIN_POL_BITU) statusIr = IR_RESTART;

		// restart odbioru jeœli czas na jeden pol bit zostanie przekroczony
		if( szerokoscIr > MAX_BIT ) statusIr = IR_RESTART;

		//jeœli szerokoœc pol bitu miesci sie w ramach czasowych to OK
		if (statusIr == IR_OK)
		{
			//inkrementacja licznika pol bitow
			if (szerokoscIr > MAX_POL_BITU) irCnt++;

			//dekodowanie bitow
			if (irCnt > 1)
			if ((irCnt % 2) == 0)
			{
				odebranaIr = odebranaIr << 1;	//zapisywanie w zmiennej odebranaIr
				if((TCCR1B & (1<<ICES1))) odebranaIr |= 0x0001;
				IrSzerCnt++;

				//jeœli odebrano poprawnie ca³¹ ramke danych
				if (IrSzerCnt > 12)
				{
					//jesli wczesniejsze dane zostaly odczytane w programie
					if (IR_flaga == 0)
					{
						//rozdzielenie odebranaIR na sk³adowe
						IR_komenda = odebranaIr & 0b0000000000111111;
						IR_adres = (odebranaIr & 0b0000011111000000) >> 6;
						IR_toggle = (odebranaIr & 0b0000100000000000) >> 11;
					}
					statusIr = IR_RESTART;
					IR_flaga = 1;
				}
			}
			irCnt++;
		}
	}

	//zerowanie licznika przy restarcie
	if (statusIr == IR_RESTART)	{
		irCnt = 0;
		TCCR1B &= ~(1<<ICES1);
	}
}

