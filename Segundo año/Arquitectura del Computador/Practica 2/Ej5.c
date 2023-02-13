//Ejercicio 5

//Representamos el numero 1,75*2^(-79) en IEEE 754 con precision simple
//Parte entera: (1)_10=(1)_2
//Parte fraccionaria:
//0,75*2=1,5 -> b_(-1)=1
//0,5*2=1 -> b_(-2)=1
//(0,75)_10=(0,11)_2

//Juntamos la parte fraccionaria y entera y obtenemos:
//(1,75)_10=(1,11)_2

//Se le aplica al exponente -79 el sesgo de precision simple, el cual es 127:
//-79+127=48
//Luego, (48)_10=(110000)_2

//Por ultimo obtenemos la representacion del numero dado en IEEE 754:
//0 | 00110000 | 11000000000000000000000

//Luego sumamos al otro numero, el cual es: 0|00110000|10100000000000000000000

//Los exponentes de ambos numeros son iguales, pasaremos entonces a aumentar el exponente
//de ambas por una unidad y desplazamos las mantisas a la derecha en una unidad, lo que dara como resultado:

//0 | 00110001 | 11100000000000000000000
//0 | 00110001 | 11010000000000000000000

//ATENCION: Estos numeros no estan representados en el sistema IEEE 754, puesto que ambos tienen un "0," implicito,
//que surgio al realizar el desplazamiento a la derecha de las mantisas. Pasamos a realizar la suma, la cual generara
//un overflow. Pero este 1 que surge del overflow pasara al lugar donde se encuentra el cero implicito,
//dando como resultado un uno implicito, volviendo a la estandarizacion IEEE 754, y la mantisa que surge de la suma
//de mantisas (sin tener en cuenta el 1 del overflow) sera la mantisa que se utilizara en el resultado final.

//En conclusion:

//0 | 00110000 | 11000000000000000000000 + 0|00110000|10100000000000000000000 = 0|00110001|10111000000000000000000
