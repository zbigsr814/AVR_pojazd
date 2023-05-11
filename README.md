# AVR_pojazd
program do sterowania pojazdem zdalnie sterowanym przez podczerwień, wykorzystano protokół RC5. Program jest napisany na uC Atmega8. Program spełnia dwie funkcje:
 
1. Odbiera dane przesyłane przez pilot na podczerwień. Jako odbiornik podczerwieni został wykorzystany układ TSOP3631. W uC następuje analiza odebranych danych i odpowiednie reakcje programu.

2. Steruje pracą pojazdu zdalnie sterowanego. Jest to małogabarytowy pojazd który posiada 4 koła typu mecanum. Pojazd posiada 4 silniki które są niezależnie od siebie sterowane, umożliwia to jazdę pojazdu: do przodu, do tyłu, w lewo, w prawo, obrót lewo/prawo, jazdę po skosie. Sterownik został wykonany na płytce drukowanej, posiada 4 mostki H do sterowania silnikami, zasilanie z akumulatorów litowo-jonowych 4x3,6V, przetwornice step-down.

Wykonany program zastosowano w pracy inżynierskiej na kierunku mechatronika. Praćę można zobaczyć w pliku pdf.
