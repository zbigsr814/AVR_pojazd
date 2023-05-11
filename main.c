#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>	//import bibliotek z toolchaina

#include "IR/ir.h"
#include "LCD/lcd44780.h"
#include "ADC/adc.h"
#include "motor/motor.h"	//import pozosta�ych plik�w programu

volatile uint8_t pwm = 100;

//funkcja inicjalizuj�ca timer2
void Timer2_init(void)
{
	TCCR2|= (1<<WGM21);		//CTC
	TCCR2|= (1<<CS22);		//prescaler 64
	TIMSK|= OCIE2;			//zezwolenie przerwania od Timer0

	OCR2 = 1;			//f_przerwania_timera2 = 100kHz
}

int main(void)
{
	cli();			//zablok�j przerwania
	ir_init();		//inicjalizacja modolu odczyttu RC5
	//lcd_init();
	//Timer2_init();	//Inicjalizacja Timera2
	//AdcInit();		//inicjalizacaj przetwornika ADC
	sei();			//odblok�j przerwania

	//lcd_cls();
	//lcd_str("Start");

	while(1)
	{
		if(IR_flaga)	//sprawd� czy odebrano dane RC5
		{
			ir2motors(IR_komenda);	//wyster�j pojazd
			IR_flaga = 0;			//wyczy�c flage odbioru danch RC5
			_delay_ms(200);			//czekaj 200ms
		}
		else		//je�li nie odebrano �adnych danych to zatrzymaj pojazd
		{
			ruch_pojazdu(stop);
		}
	}

}


//------------------------------------------ Przerwanie timer2
//ISR(TIMER2_COMP_vect)
//{
//	static uint8_t cnt = 0;
//	cnt++;
//	if(cnt >= 101) cnt = 0;			//licznik zliczajacy w g�re 0-100
//
//	if(cnt < pwm) ruch_pojazdu(stop);
//	else ir2motors(IR_komenda);		//realizacja prorogramowa PWM
//}
