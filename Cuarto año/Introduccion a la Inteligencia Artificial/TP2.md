# Presentacion TPN°2: Catalogacion de genero de pelicula

## Integrantes del grupo:
- Navall, Nicolás Uriel
- Noguera, Dante

## Estructura del arbol:

Raiz Pelicula - Genero (Caracteristicas en la seccion de "Genero") - Subgenero (Caracteristicas en la seccion "Subgenero").

## Raiz Pelicula
pelicula(X) :- satisface(tiene_nombre, X), satisface(min_runtime_90min, X), satisface(fecha_estreno, X)

## Genero (primer nivel)

- terror(X) :- pelicula(X), satisface(hace_sentir_miedo,X), satisface(tiene_jumpscare,X).
- comedia(X) :- pelicula(X), satisface(hace_reir,X), satisface(tiene_juego_de_palabras,X).
- accion(X) :- pelicula(X), satisface(tiene_persecusion,X), satisface(tiene_combate,X).
- drama(X) :- pelicula(X), satisface(tiene_conflicto_de_intereses,X),satisface(tiene_tragedia,X).

## Subgeneros (segundo nivel)

### Subgeneros de Terror

- ciencia_ficcionT(X) :- terror(X),satisface(tiene_tecnologia_avanzada,X).
- fantasiaT(X) :- terror(X),satisface(tiene_magia,X).
- historicaT(X) :- terror(X),satisface(ocurre_en_el_pasado,X).
- realistaT(X) :- terror(X),satisface(puede_pasar_actualmente,X).

### Subgeneros de Comedia

- ciencia_ficcionC(X) :- comedia(X),satisface(tiene_tecnologia_avanzada,X).
- fantasiaC(X) :- comedia(X),satisface(tiene_magia,X).
- historicaC(X) :- comedia(X),satisface(ocurre_en_el_pasado,X).
- realistaC(X) :- comedia(X),satisface(puede_pasar_actualmente,X).

### Subgeneros de Accion

- ciencia_ficcionA(X) :- accion(X),satisface(tiene_tecnologia_avanzada,X).
- fantasiaA(X) :- accion(X),satisface(tiene_magia,X).
- historicaA(X) :- accion(X),satisface(ocurre_en_el_pasado,X).
- realistaA(X) :- accion(X),satisface(puede_pasar_actualmente,X).

### Subgeneros de Drama

- ciencia_ficcionD(X) :- drama(X),satisface(tiene_tecnologia_avanzada,X).
- fantasiaD(X) :- drama(X),satisface(tiene_magia,X).
- historicaD(X) :- drama(X),satisface(ocurre_en_el_pasado,X).
- realistaD(X) :- drama(X),satisface(puede_pasar_actualmente,X).

### Ejemplos

- "Whiplash" es una pelicula donde hay conflicto de intereses, una tragedia y puede suceder en la cotidianidad.
- "Arrival" es una pelicula donde hay conflicto de intereses, una tragedia y tiene tecnologia avanzada.
- "Inception" es una pelicula donde hay persecuciones, tiene combates y tecnologia avanzada.
- "Monty Python and The Holy Grail" es una pelicula que te hace reir, tiene juego de palabras y magia.
- "Alien" es una pelicula que te hace sentir miedo, tiene jumpscares y tecnologia avanzada.
- "The Hitchhiker's Guide to the Galaxy" es una pelicula que te hace reir, tiene juego de palabras y tecnologia avanzada.
- "As Good as it Gets" es una pelicula que te hace reir, tiene juego de palabras y puede suceder actualmente.
