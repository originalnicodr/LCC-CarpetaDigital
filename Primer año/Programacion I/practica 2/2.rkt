;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |2|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define (distanciaxy x y) (sqrt (+ (sqr x) (sqr y))))

;Repesenta distancia y puntos en un plano con numeros
;distancia-dos-puntos Number Number Number Number -> Number
;Recibe dos puntos en un plano y devuelve la distancia entre ellos
;(distancia-dos-puntos 1 1 1 1)=0
;(distancia-dos-puntos 1 2 5 5)=5
;(distancia-dos-puntos 2 2 2 -2)=4

(define (distancia-dos-puntos x1 y1 x2 y2) (distanciaxy (- x1 x2) (- y1 y2)))

(check-expect (distancia-dos-puntos 1 1 1 1) 0)
(check-expect (distancia-dos-puntos 1 2 5 5) 5)
(check-expect (distancia-dos-puntos 2 2 2 -2) 4)