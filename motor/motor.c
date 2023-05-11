#include <avr/io.h>
#include "motor.h"
#include "../makra.h"	//import pozosta³ych plików programu

// po³o¿enie silników oraz przyjêty kierunek
// o - kropka narysowana markerem na ramie
//		o[0]	[1]
//
//
//
//       [2]	[3]

volatile uint8_t pwm;	//wartoœc sygna³u PWM

//ruch silnika M0 kierunek lewo/prawo
void M0_ruch(ruch_silnika kierunek)
{
	if(kierunek == motorPrawo)
	{
		PORT(M0_prawo_port) |= (1<<M0_prawo);
		PORT(M0_lewo_port) &= ~(1<<M0_lewo);
	}
	else if(kierunek == motorLewo)
	{
		PORT(M0_lewo_port) |= (1<<M0_lewo);
		PORT(M0_prawo_port) &= ~(1<<M0_prawo);
	}
	else
	{
		PORT(M0_lewo_port) &= ~(1<<M0_lewo);
		PORT(M0_prawo_port) &= ~(1<<M0_prawo);
	}
}

//ruch silnika M1 kierunek lewo/prawo
void M1_ruch(ruch_silnika kierunek)
{
	if(kierunek == motorPrawo)
	{
		PORT(M1_prawo_port) |= (1<<M1_prawo);
		PORT(M1_lewo_port) &= ~(1<<M1_lewo);
	}
	else if(kierunek == motorLewo)
	{
		PORT(M1_lewo_port) |= (1<<M1_lewo);
		PORT(M1_prawo_port) &= ~(1<<M1_prawo);
	}
	else
	{
		PORT(M1_lewo_port) &= ~(1<<M1_lewo);
		PORT(M1_prawo_port) &= ~(1<<M1_prawo);
	}
}

//ruch silnika M2 kierunek lewo/prawo
void M2_ruch(ruch_silnika kierunek)
{
	if(kierunek == motorPrawo)
	{
		PORT(M2_prawo_port) |= (1<<M2_prawo);
		PORT(M2_lewo_port) &= ~(1<<M2_lewo);
	}
	else if(kierunek == motorLewo)
	{
		PORT(M2_lewo_port) |= (1<<M2_lewo);
		PORT(M2_prawo_port) &= ~(1<<M2_prawo);
	}
	else
	{
		PORT(M2_lewo_port) &= ~(1<<M2_lewo);
		PORT(M2_prawo_port) &= ~(1<<M2_prawo);
	}
}

//ruch silnika M3 kierunek lewo/prawo
void M3_ruch(ruch_silnika kierunek)
{
	if(kierunek == motorPrawo)
	{
		PORT(M3_prawo_port) |= (1<<M3_prawo);
		PORT(M3_lewo_port) &= ~(1<<M3_lewo);
	}
	else if(kierunek == motorLewo)
	{
		PORT(M3_lewo_port) |= (1<<M3_lewo);
		PORT(M3_prawo_port) &= ~(1<<M3_prawo);
	}
	else
	{
		PORT(M3_lewo_port) &= ~(1<<M3_lewo);
		PORT(M3_prawo_port) &= ~(1<<M3_prawo);
	}
}

//ruch ca³ego pojazdu, funkcja steruje czterema silnikami
void ruch_pojazdu(ruch_silnikow kierunek)
{
	switch(kierunek)
	{
	case przod:
		M0_ruch(motorLewo);
		M1_ruch(motorLewo);
		M2_ruch(motorLewo);
		M3_ruch(motorLewo);
		break;
	case tyl:
		M0_ruch(motorPrawo);
		M1_ruch(motorPrawo);
		M2_ruch(motorPrawo);
		M3_ruch(motorPrawo);
		break;
	case lewo:
		M0_ruch(motorPrawo);
		M1_ruch(motorLewo);
		M2_ruch(motorLewo);
		M3_ruch(motorPrawo);
		break;
	case prawo:
		M0_ruch(motorLewo);
		M1_ruch(motorPrawo);
		M2_ruch(motorPrawo);
		M3_ruch(motorLewo);
		break;
	case przodPrawo:
		M0_ruch(motorLewo);
		M1_ruch(motorStop);
		M2_ruch(motorStop);
		M3_ruch(motorLewo);
		break;
	case przodLewo:
		M0_ruch(motorPrawo);
		M1_ruch(motorStop);
		M2_ruch(motorStop);
		M3_ruch(motorPrawo);
		break;
	case tylPrawo:
		M0_ruch(motorStop);
		M1_ruch(motorLewo);
		M2_ruch(motorLewo);
		M3_ruch(motorStop);
		break;
	case tylLewo:
		M0_ruch(motorStop);
		M1_ruch(motorPrawo);
		M2_ruch(motorPrawo);
		M3_ruch(motorStop);
		break;
	case obrotPrawo:
		M0_ruch(motorLewo);
		M1_ruch(motorPrawo);
		M2_ruch(motorLewo);
		M3_ruch(motorPrawo);
		break;
	case obrotLewo:
		M0_ruch(motorPrawo);
		M1_ruch(motorLewo);
		M2_ruch(motorPrawo);
		M3_ruch(motorLewo);
		break;
	case stop:
		M0_ruch(motorStop);
		M1_ruch(motorStop);
		M2_ruch(motorStop);
		M3_ruch(motorStop);
		break;
	}
}

//przepisanie odczytanego kodu podczerwieni do ruchu pojazdu
void ir2motors(uint8_t war_ir)
{
	switch(war_ir)
	{
	case 32: ruch_pojazdu(przod); break;
	case 33: ruch_pojazdu(tyl); break;
	case 17: ruch_pojazdu(obrotLewo); break;
	case 16: ruch_pojazdu(obrotPrawo); break;

	case 2: ruch_pojazdu(przod); break;
	case 8: ruch_pojazdu(tyl); break;
	case 4: ruch_pojazdu(lewo); break;
	case 6: ruch_pojazdu(prawo); break;

	case 1: ruch_pojazdu(przodLewo); break;
	case 3: ruch_pojazdu(przodPrawo); break;
	case 7: ruch_pojazdu(tylLewo); break;
	case 9: ruch_pojazdu(tylPrawo); break;

	case 38: pwm += 10; if(pwm > 100) pwm = 0; break;
	case 15: pwm -= 10; if(pwm > 240) pwm = 100; break;

	case 59: ruch_pojazdu(stop); break;
	}
}
