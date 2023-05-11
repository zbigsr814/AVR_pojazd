#ifndef MOTOR_MOTOR_H_
#define MOTOR_MOTOR_H_

//po³o¿enie silników wzglendem ramy
//		 [0]	[2]
//
//		 [1]   o[3]

//zdefiniowanie wyprowadzeñ MCU dla sterowania silnikiem M0
#define M0_lewo_port D
#define M0_lewo 4
#define M0_prawo_port D
#define M0_prawo 3

//zdefiniowanie wyprowadzeñ MCU dla sterowania silnikiem M1
#define M1_lewo_port D
#define M1_lewo 5
#define M1_prawo_port D
#define M1_prawo 6

//zdefiniowanie wyprowadzeñ MCU dla sterowania silnikiem M2
#define M2_lewo_port B
#define M2_lewo 1
#define M2_prawo_port B
#define M2_prawo 2

//zdefiniowanie wyprowadzeñ MCU dla sterowania silnikiem M3
#define M3_lewo_port C
#define M3_lewo 0
#define M3_prawo_port C
#define M3_prawo 1

//definicja enumeratora dla ruchu pojedynczym silnikiem
typedef enum
{
	motorPrawo, motorLewo, motorStop
} ruch_silnika;

//definicja enumeratora dla ruchu ca³ego pojazdu
typedef enum
{
	przod, tyl, lewo, prawo, przodLewo, przodPrawo, tylLewo, tylPrawo,
	obrotLewo, obrotPrawo, stop
} ruch_silnikow;

extern volatile uint8_t pwm;	//wartoœc sygna³u PWM

void M0_ruch(ruch_silnika kierunek);	//ruch silnika M0 kierunek lewo/prawo
void M1_ruch(ruch_silnika kierunek);	//ruch silnika M1 kierunek lewo/prawo
void M2_ruch(ruch_silnika kierunek);	//ruch silnika M2 kierunek lewo/prawo
void M3_ruch(ruch_silnika kierunek);	//ruch silnika M3 kierunek lewo/prawo
void ruch_pojazdu(ruch_silnikow kierunek);	//ruch ca³ego pojazdu
void ir2motors(uint8_t war_ir);				//przepisanie odczytanego kodu podczerwieni
											//do ruchu pojazdu

#endif /* MOTOR_MOTOR_H_ */
