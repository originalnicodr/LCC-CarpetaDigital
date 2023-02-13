;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |4|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
;Representa una longitud y un area en numeros
;area-cubo Number -> Number
;Recibe la longitud de una arista de un cubo y devuelve su area
;(area-cubo 1)=6
;(area-cubo 2)=24
;(area-cubo 4)=96

(define (area-cubo l) (* (* l l) 6))

(check-expect (area-cubo 1) 6)
(check-expect (area-cubo 2) 24)
(check-expect (area-cubo 4) 96)