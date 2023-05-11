#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>	//import bibliotek z toolchaina

#include "IR/ir.h"
#include "LCD/lcd44780.h"
#include "ADC/adc.h"
#include "motor/motor.h"	//import pozosta³ych plików programu

volatile uint8_t pwm = 100;

//funkcja inicjalizuj¹ca timer2
void Timer2_init(void)
{
	TCCR2|= (1<<WGM21);		//CTC
	TCCR2|= (1<<CS22);		//prescaler 64
	TIMSK|= OCIE2;			//zezwolenie przerwania od Timer0

	OCR2 = 1;			//f_przerwania_timera2 = 100kHz
}

int main(void)
{
	cli();			//zablokój przerwania
	ir_init();		//inicjalizacja modolu odczyttu RC5
	//lcd_init();
	//Timer2_init();	//Inicjalizacja Timera2
	//AdcInit();		//inicjalizacaj przetwornika ADC
	sei();			//odblokój przerwania

	//lcd_cls();
	//lcd_str("Start");

	while(1)
	{
		if(IR_flaga)	//sprawdŸ czy odebrano dane RC5
		{
			ir2motors(IR_komenda);	//wysterój pojazd
			IR_flaga = 0;			//wyczyœc flage odbioru danch RC5
			_delay_ms(200);			//czekaj 200ms
		}
		else		//jeœli nie odebrano ¿adnych danych to zatrzymaj pojazd
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
//	if(cnt >= 101) cnt = 0;			//licznik zliczajacy w góre 0-100
//
//	if(cnt < pwm) ruch_pojazdu(stop);
//	else ir2motors(IR_komenda);		//realizacja prorogramowa PWM
//}
