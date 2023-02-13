;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |5|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(require 2htdp/image)
;Representamos area de una imagen con numeros
;area-imagen Image -> Number
;Recibe una imagen y devuelve el area de esta
;(area-imagen (rectangle 1 1 "solid" "green"))=1
;(area-imagen (rectangle 5 5 "solid" "green"))=25
;(area-imagen (rectangle 2 3 "solid" "green"))=6

(define (area-imagen i) (*(image-width i) (image-height i)))

(check-expect (area-imagen (rectangle 1 1 "solid" "green")) 1)
(check-expect (area-imagen (rectangle 5 5 "solid" "green")) 25)
(check-expect (area-imagen (rectangle 2 3 "solid" "green")) 6)