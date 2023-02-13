;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |1|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
;Representamos distancia con coordenadas x e y en forma de numeros
;distanciaxy: Number Number -> Number
;Recube un punto en el plano y devuelve su distancia al punto de origen
;(distancia 4 3)=5

(define (distanciaxy x y) (sqrt (+ (sqr x) (sqr y))))

(check-expect (distanciaxy 4 3) 5)