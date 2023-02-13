# 1)
## a)
```
FAT    | 4 | -1 | 0 | 5 | 6 | 7 | -1 | -1 | 0 |
CLUSTER  1    2   3   4   5   6    7    8   9
```

## b)
Uno de los errores es que el cluster 1 y 2 no estan asociados a ningun archivo, ya que
los archivos que tienen el disco no utilizan esos sectores, por lo que deberian estar
marcados con un 0. Ademas, el cluster 1 apunta al cluster 4, el cual es en si el cluster
inicial señalado por un archivo, lo cual no tiene sentido que este siendo apuntado
por otro.

## c) Cambiaria el cluster al que esta apuntando el sector 7 por el cluster 2, y que este
indique que no hay mas clusters con un -1.

# 2)

## a)
```
Bitmanp
      | 1 | 1 | 1 | 0 | 0 | 0 |
Bloque  0   1   2   3   4   5



Inode 0

Size        600
Block 0     2
Block 1     0
Link Count  1



Inode 1

Size        1
Block 0     1
Block 1     -1
Link Count  2
```

## b)
```
/ Directory
(file1 ,1)
(file2 ,0)
(file1 ,1)
(file1_copia ,2)

Bitmanp
      | 1 | 1 | 1 | 1 | 0 | 0 |
Bloque  0   1   2   3   4   5

Inode 2

Size        1
Block 0     3
Block 1     -1
Link Count  1
```


Correccion Esteban:

Está muy bien la práctica.

Un detalle para el ejercicio 1: no decís cómo solucionar los problemas.
Una solución es liberar los clusters 1 y 2 pero se puede hacer algo mejor:
como no sabemos si esos clusters tienen información útil podemos intentar
recuperar la información y guardarla con algún nombre ficticio (en linux
el fsck guarda esta información recuperada en /lost+found, windows en
archivos llamados: <nnnn>.chk.

En este caso, para el cluster 2 no hay mucho para hacer: puesto que no hay
ninguna entrada (direntry o entrada en la fat) que apunte al cluster2 lo
más que se puede hacer es crear un nuevo archivo que contenga ese cluster.
Problemas apartes, que tendrá que resolver el usuario: ¿cómo saber de qué
tipo es el archivo? ¿cómo saber su tamaño? (la corrección
lo dejará del tamaño de un cluster)

En el caso del cluster 1 es un poco más complicada la cosa:
- Una opción es crear un archivo que tenga sólo el cluster 1 (i.e.:
suponer que es parte de un archivo perdido de un sólo cluster).
- Otra opción es crear un archivo que tenga el cluster 1 y una copia del
resto de la cadena, es decir una copia de los clusters 4,5,6,7 (en este
caso nos quedamos sin espacio para hacer esto, pero la idea
es válida igual). Al fin y al cabo tampoco podemos estar seguro que la
entrada de directorio para el archivo A.txt esté correcta.

Saludos
