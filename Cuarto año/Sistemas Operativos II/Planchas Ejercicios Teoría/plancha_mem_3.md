# 1 a
```
Traza: 1 (7) 2 (4) (5) 3 5 1 3 5 6

Traza   1           (7)          2          (4)         (5)          3           5           1           3           5           6
Frame -|1|<1,0>     |1|<1,0>    |1|<1,0>    |1|<1,0>    |1|<1,0>   -|3|<1,0>    |3|<1,0>    |3|<1,0>   -|3|<1,0>    |3|<1,0>    |3|<1,0>
       | |<0,0>    -|7|<1,1>    |7|<1,1>    |7|<1,1>    |7|<1,1>    |7|<0,1>    |7|<0,1>    |7|<0,1>    |7|<0,1>    |7|<0,1>   -|6|<1,0>
       | |<0,0>     | |<0,0>   -|2|<1,0>    |2|<1,0>    |2|<1,0>    |2|<0,0>    |2|<0,0>   -|1|<1,0>    |1|<1,0>    |1|<1,0>    |1|<1,0>
       | |<0,0>     | |<0,0>    | |<0,0>   -|4|<1,1>    |4|<1,1>    |4|<0,1>    |4|<0,1>    |4|<0,1>    |4|<0,1>    |4|<0,1>    |4|<0,1>
       | |<0,0>     | |<0,0>    | |<0,0>    | |<0,0>   -|5|<1,1>    |5|<0,1>   -|5|<1,1>    |5|<1,1>    |5|<1,1>   -|5|<1,1>    |5|<1,1>
```
Fallos de pagina:8
Aciertos:3
Lecturas al disco:8
Escrituras al disco:1

# b
```
Traza   1    (7)     2      (4)     (5)      3       5       1       3       5       6
Frame  |1|   |1|    |1|     |1|     |1|     |1|     |1|     |1|     |1|     |1|     |6|
       | |   |7|    |7|     |7|     |7|     |7|     |7|     |7|     |7|     |7|     |7|
       | |   | |    |2|     |2|     |2|     |3|     |3|     |3|     |3|     |3|     |3|
       | |   | |    | |     |4|     |4|     |4|     |4|     |4|     |4|     |4|     |4|
       | |   | |    | |     | |     |5|     |5|     |5|     |5|     |5|     |5|     |5|
```

Fallos de pagina:7
Aciertos:4
Lecturas al disco:7
Escrituras al disco:0

# 2

El algoritmo optimo sirve como cota para el resto de los algoritmos, ningun otro algoritmo sera mejor que este. Si puede darse el caso que
el algoritmo FIFO tenga el mismo resultado que el algoritmo optimo, pero no significa que este sea mejor.

# 3 a
```
--------------------------------------------
|     512    |  | 128 |  |B(128)|A(128)|   |
--------------------------------------------
```
Liberamos el bloque A. Como el bloque B comienza en la pagina n° 4096 (la cual es multiplo de 2), como el bloque A ahora liberado tiene el
mismo tamaño que B y el bloque que comienza en la pagina 4096 puede tener cualquier tamaño (multiplo de 2) podemos fusionar ambos bloques.

```
--------------------------------------------
|     512    |  | 128 |  |     256     |   |
--------------------------------------------
```
# c
Se pide un bloque C de 128 paginas luego de liberar el bloque A, pasara a ocupar el primer hueco lo suficientemente grnde como para satisfacer el pedido
```
--------------------------------------------
|     512   |  |C(128)|  |     256     |   |
--------------------------------------------
```

# 4
Podria darse el caso de tener una base de datos de cuentas bancarias en la que se retira una suma de dinero de una cuenta. Se descuenta el dinero
de la cuenta y se procedera a mandar la pagina en la que esta se encuentra al archivo swap correspondiente, pero antes de poder escribir en dicho
archivo se pide el saldo de la cuenta, por lo cual se requerira revisar la pagina que se acaba de mandar al swap, y pasara a leerse una version
anterior de la pagina que indicara que la cuenta tiene mas dinero del que deberia.



Correccion de Esteban:

Un detalle: en el último acceso a la página 5 actualizan el puntero sin
necesidad, eso causa que se reemplace una página que no debería
reemplazarse. Revisalo y cualquier cosa me consultás, pero no hace falta
que lo corrijas.
