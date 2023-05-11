#include <avr/io.h>
#include <util/delay.h>

void AdcInit(void)	//inicjalizacja przetwornika ADC w tryb pollingu
{
	ADMUX|= (1<<REFS0);    				//nap odniesienia 5V
	ADMUX|= (1<<ADLAR);               //8-bitowy wynik przetwornika
	ADCSRA|= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //ADC w³¹czone i preskaler 64
	//ADCSRA|= (1<<ADFR)|(1<<ADIE);    //free runing mode i w³¹czenie przerwañ ADC
	//ADCSRA|= (1<<ADSC);				//ustawienie flagi wykonania pomiaru
}

uint16_t AdcPomiar(uint8_t kanal)	//funkcja wykonuj¹ca pomiar ADC
{
	ADMUX&= ~((1<<MUX0)|(1<<MUX1)|(1<<MUX2));//pomiar z pojedynczego wyprowadzenia ADC
	ADMUX|= (ADMUX & 0xf8) | kanal;			//wybór badanego kanalu
	ADCSRA|= (1<<ADSC);						//ustawienie flagi wykonania pomiaru
	while(ADCSRA & (1<<ADSC));				//czekaj na dokonanie pomiaru
	return ADCW;							//zwróc wynik pomiaru
}
