# 1

Si tubo exito el fork y estoy parado en el hijo ejecuto ls (da 0 a si mismo y su PID al padre)

"/bin/ls" es el comando ls que lista archvos del directorio

Antes de ejecutar la funcion execve se crea un proceso hijo en el fork. De realizarse exitosamente, el proceso pasara a entrar en el if
(el padre no podra entrar ya que el resultado de la funcion fork le dara el PID del hijo). En este punto el proceso comparte las mismas
paginas que el padre, marcandolas como "read only". Cuando el hijo ejecuta la funcion execve con el argumento "/bin/ls" ejecutara la
funcion de UNIX ls, la cual listara los archivos del directorio. Al ocurrir esto las paginas del proceso hijo no seran exactamente
igual a las del proceso padre, y se pasara a copiar (marcando la nueva pagina como lectura/escritura) las que sean modificadas por la
ejecucion de execve, perteneciendo estas solo al proceso hijo.

Antes de la ejecucion de execve

```
Proceso     Memoria    Proceso
Padre                     Hijo

1 |p1|------>|p1|<------|p1| 1 
2 |p2|---.   |  |   .---|p2| 2
3 |p3|-. '-->|p2|<--' .-|p3| 3
       |     |  |     |
       '---->|p3|<----'
             |  |
```

Paginas marcadas con CoW (copy on write): p1, p2, p3.

Despues de la ejecucion de execve

```
Proceso     Memoria      Proceso
Padre                       Hijo

1 |p1|------>|p1 |  .----|p1'| 1 
2 |p2|---.   |p1'|<-'.---|p2 | 2
3 |p3|-. '-->|p2 |<--' .-|p3 | 3
       |     |   |     |
       '---->|p3 |<----'
             |   |
```

Paginas marcadas con CoW (copy on write): p1, p2, p3.
Paginas marcadas como lectura y escritura: p1'

# 2
Tenemos 5 marcos de pagina y la siguiente traza de acceso a memoria: 1 7 2 4 5 3 5 1 3 5 6

A continuacion

```
Cadena de referencia -->
 1   7   2   4   5   3   5   1   3   5   6  
 |   |   |   |   |   |   |   |   |   |   |  
 v   v   v   v   v   v   v   v   v   v   v  
|1| |1| |1| |1| |1| |3| |3| |3| |3| |3| |3| 
|-| |7| |7| |7| |7| |7| |7| |1| |1| |1| |1| 
|-| |-| |2| |2| |2| |2| |2| |2| |2| |2| |6|
|-| |-| |-| |4| |4| |4| |4| |4| |4| |4| |4| 
|-| |-| |-| |-| |5| |5| |5| |5| |5| |5| |5| 
```

Se produjeron 3 aciertos de pagina y 8 fallos de pagina.

Realiza 8 lecturas al disco y 3 escrituras.
```
Lectura ||||||||
Escritura |||
```


Correccion de Esteba:

Está muy bien. Un detalle: luego del exec, las páginas del padre que ya no
quedan referenciadas por el hijo pierden la marca de COW (no tiene sentido
en este caso copiarlas en otro lado cuando se escriban).