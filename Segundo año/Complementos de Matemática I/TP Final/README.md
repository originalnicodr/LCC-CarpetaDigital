Dibujador de grafos

Versión 1.2

Blanco Fernando, Navall Nicolas


Version de Python: 2.7.15

Version de pygame utilizada (windows): 1.9.1 y 1.9.4

Para ejecutar el programa debe utilizarse draw_graph.py. Para utilizar algunos de los argumentos opcionales utilice el argumento -h (help).



Para optimizar el algoritmo en grafos de muchos vertices y aristas lo que hicimos fue dividir el area de dibujo en secciones utilizando una grilla, en la cual la cantidad
 de secciones esta ligada a la cantidad de vertices. Luego, se calculan las fuerzas de repulsion con los vertices que se encuentran en la misma casilla o en las casillas 
vecinas, lo que reduce la cantidad de calculos.

Ademas, modificamos el algoritmo de calculo de fuerzas de repulsion para que al calcular una fuerza de repulsion de un vertice a otro, se asigne la fuerza opuesta a la 
fuerza de repulsion de este otro vertice al anterior, ahorrandonos asi mas calculos a medida que calculamos las fuerzas de mas vertices.



Para ejecutar el programa se corre el archivo “draw_graph.py” por linea de comando y se debe pasar un archivo .txt como argumento el cual deberá contener el grafo, el programa cuenta con distintas opciones de “modo verbose”, “fullscreen”, cantidad de iteraciones, muestra de tiempo de ejecución, “modo optimizado”, dibujar la cuadricula, cambiar las constantes C y de temperatura, dibujar cada paso, para más información de esto corra el archivo con -h.

El resto de los archivos de python se utilizan como librerías las cuales tienen las funciones necesarias para el funcionamiento del programa separadas por categorías.

Para la prueba del programa les facilitamos archivos .txt que contienen grafos, los llamados dataxx.txt son grafos sencillos y los grafotestx.txt son de mayor tamaño los cuales tardan un tiempo mayor a 1s sin optimización y menos a 0.5s con la misma.
(Las x en el nombre de los archivos representan el lugar de un número).



Nota de versión: 
Se corrigió el error que se generaba al correr los grafotestx.txt en Linux, el cual se debía a que los mismo fueron generados en Windows por lo que tenían un carácter '\r' extra, para esto se modifico la lectura para que detecte el mismo y lo ignore.

Se agregaron grafos grandes de prueba generados en Linux.


Ademas, modificamos el algoritmo de calculo de fuerzas de repulsion para que al calcular una fuerza de repulsion de un vertice a otro, se asigne la fuerza opuesta a la
fuerza de repulsion de este otro vertice al anterior, ahorrandonos asi mas calculos a medida que calculamos las fuerzas de mas vertices.