;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |3|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
;Representamos longitud y volumen con numeros
;vol-cubo Number -> Number
;Recibe la longitud de una arista y calcula el volumen de un cubo
;(vol-cubo 2)=8
;(vol-cubo 3)=27
;(vol-cubo 5)=125
(define (vol-cubo a) (* a a a))

(check-expect (vol-cubo 2) 8)
(check-expect (vol-cubo 3) 27)
(check-expect (vol-cubo 5) 125)