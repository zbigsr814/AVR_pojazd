#ifndef MAKRA_H_
#define MAKRA_H_

// Makra upraszczaj¹ce dostêp do rejestru PORTx
#define PORT(x) ZPORT(x)
#define ZPORT(x) (PORT##x)

// Makra upraszczaj¹ce dostêp do rejestru PINx
#define PIN(x) ZPIN(x)
#define ZPIN(x) (PIN##x)

// Makra upraszczaj¹ce dostêp do rejestru DDRx
#define DDR(x) ZDDR(x)
#define ZDDR(x) (DDR##x)


#endif /* MAKRA_H_ */
