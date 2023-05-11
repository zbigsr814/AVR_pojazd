#ifndef IR_H_
#define IR_H_

#define IR_PORT B				//okre�lenie portu na kt�rym si� znajduje ICR
#define IR_PIN 0				//
#define IR_IN (1<<IR_PIN)		//


//okre�lenie preskalera dla timera1
#define TIMER1_PRESCALER 64

//konwercja taktowania przerwania na milisekundy
#define ir_micro_s(dec) ((dec)*(F_CPU/1000000)/TIMER1_PRESCALER)

//okre�lenie min/max dlugosci pol bitu z tolerancja
#define TOLERANCJA 200
#define MIN_POL_BITU 	ir_micro_s(889	- TOLERANCJA)
#define MAX_POL_BITU 	ir_micro_s(889 + TOLERANCJA)
#define MAX_BIT ir_micro_s((889+889) + TOLERANCJA)

//flaga informuj�ca ze dane sa gotowe do odbioru
extern volatile uint8_t IR_flaga;

//sk�adowe odebrane przez RC5
extern volatile uint8_t IR_toggle;		// bit TOGGLE
extern volatile uint8_t IR_adres;		// adres
extern volatile uint8_t IR_komenda;		// komenda

//inicjalizacja modolu
void ir_init();		//funkcja inicjalizujaca


#endif /* IR_H_ */
