# 1) a)
No tienen fragmentacion externa por que se esta usando paginacion?
El programa A tendra una fragmentacion interna de 58 bits y el programa B una fragmentacion interna de 4 bits.
# b)
Se divide la memoria fisica en marcos de igual tamaño (potencia de dos), y la memoria requerida por los programas se separa en paginas de igual tamaño que los marcos. Se subdivide la tabla identificadora de paginas en dos, obteniendo asi una tabla externa en la cual cada entrada apunta a otra pagina intermedia. Esta ultima sera la encargada de apuntar a la pagina real en la memoria fisica.

La ventaja de este modelo es que aprovecha mejor el espacio tipicamente vacio de la memoria de direccionamiento.

Como el tamaño de las paginas es de 128 bytes vamos a requerir al menos 10 bits de desplazamiento para alcanzar todas las direcciones de memoria de la pagina. Como la tabla de paginacion externa es de 3 bits, nos quedan 3 bits para la tabla de paginacion intermedia. Nuestra direccion virtual es de 0x1234.

Como nuestras direcciones son de 16 bits las direcciones de memoria iran desde 0000 hacia FFFF.

Tenemos que dividir las direcciones en entradas con 3 bits, por lo cual tendremos 8 diferentes entradas.

```
-----------
|0000-1FFF|
|2000-3FFF|
|4000-5FFF|
|6000-7FFF|
|8000-9FFF|
|A000-BFFF|
|C000-DFFF|
|E000-FFFF|
-----------
```

Utilizaremos la entrada 0000-1FFF y accedemos a la tabla del segundo nivel, la cual nuevamente divide las direcciones en entradas con 3 bits:

```
-----------
|0000-03FF|
|0400-07FF|
|0800-0BFF|
|0C00-0FFF|
|1000-13FF|
|1400-17FF|
|1800-1BFF|
|1C00-1FFF|
-----------
```

Accedemos a la pagina de la entrada 1000-13FF:

```
------
|1000|
|1001|
|... |
|1234|
|... |
------
```

Como en la primer tabla no nos desplazamos tomamos los primeros 3 bits de nustra direccion como 000, luego en la segunda tabla como pasamos por la entrada 1000-13FF (es decir realizamos un desplazamiento de 5 lugares
sobre la tabla de paginacion intermedia) por lo que los siguientes 3 bits de la direccion seran 101, y por ultimo aplicamos un desplazamiento de 234 lugares en la pagina alcanzada, 1000110100 en binario. Nuestra direccion fisica traducida final sera la siguiente: 000 101 1000110100

# 2)
Utilizar paginas de fragmentacion de dos (o mas) niveles conlleva a que un fallo de pagina triplique el tiempo de acceso a memoria en un sistema de 32 bits, y suxtiplique en un sistema de 64. Cada nivel de páginas conlleva un acceso adicional a memoria en caso de fallo de página.

Para solucionar el problema puede utilizarse funciones digestoras (hash functions) para mapear cada una de las páginas a un espacio muestral más pequeño. Cada página es mapeada a una lista de correspondencias simples. Sin embargo, por la alta frecuencia de accesos a una tabla, debe elegirse una funcion hash muy ágil para evitar que el tiempo que tome calcular la posición en la tabla resulte significativo frente a las alternativas.

# 3)
Fragmentación externa se produce cuando hay muchos bloques libres entre bloques ocupados con procesos y fragmentación interna se refiere a la cantidad de memoria dentro de un bloque que nunca se usará. Los problemas que traen ambas son el del uso no efectivo de la memoria fisica.







Correccion Esteban:

Hola. Encontré varios errores en tu práctica, estaría bueno que la vuelvas
a hacer. No dudes en consultarme si te quedan dudas.


Ojo en el 1, posiblemente un error de cuenta: lo que se pierde por
fragmentación interna en el proceso de 4300 bytes es 52 bytes (no 58). Y
no son bits sino bytes!!

No me queda clara la siguiente línea:
"La ventaja de este modelo es que aprovecha mejor el espacio tipicamente
vacio de la memoria de direccionamiento."

Esta sería la explicación correcta:

Otra ventaja importante de la tabla de paginación de varios niveles es que
las tablas que no se necesitan ni siquiera tienen que ser creadas. Por
ejemplo,
siguiendo con el ejemplo, si los segmentos de códigos y datos entran todos
en las direcciones que empiezan con los bits "000"
(o sea: ocupan menos de 8 Kb) y el stack entra en las direcciones que
empiezan con "111" (8 Kb de stack no está mal) entonces
las entradas que corresponden a "001", "010", "011", "100", "101" y "110"
pueden marcarse como inválidas y no ahorramos crear todas esas tablas de
segundo nivel. Con lo cual en vez de usar, para una tabla de un sólo
nivel: 4Kb (2^9 x 8 bytes) estaremos usando con dos niveles:
2^3 x 8 bytes para el primer nivel y luego 2^6*8 = 2^9 bytes para cada
tabla interior, o sea: 64 + 512 *2 = 64+1024 = 1088 bytes. Para
espacios de direcciones más grandes, el ahorro de memoria es mucho mayor.


En el b) también ponés: "128 bytes vamos a requerir al menos 10 bits " =>
no, son 7 bits los necesarios (2^7 = 128)

El resto del ejercicio también está incorrecto. Te recomiendo que leas de
nuevo cómo funciona el mecanismo de paginación con 2 o más niveles. Quizás
en el libro no está del todo claro, pero son temas clásicos así que podés
buscar cualquier artículo medianamente serio en internet o buscarlo en los
libros clásicos de sistemas operativos (o incluso de arquitectura del
computador).

El resto de la plancha se ve bien.

Saludos

Esteban