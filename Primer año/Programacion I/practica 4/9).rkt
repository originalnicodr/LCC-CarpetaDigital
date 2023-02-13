;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |9)|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")))))
(define-struct texto [s color tam])
(define INICIAL (make-texto "" "indigo" 20))
; Un texto es: (make-texto String Color Number)
; Intepretación: El primer elemento es la cadena a mostarse, mientras que el segundo y
;el tercero determinan el color y tamaño de fuente en píxeles respectivamente.

(define (string-remove-last s) (if (not(string=? "" s)) (substring s 0 (- (string-length s) 1)) s))
(define (escribir n) (place-image/align (text (texto-s n) (texto-tam n) (texto-color n))
                   0 0 "left" "top" (empty-scene 800 60)))
(define (teclado l c) (cond [(key=? c "\b") (make-texto (string-remove-last (texto-s l)) (texto-color l) (texto-tam l))]
                            [(key=? c "f1") (make-texto (texto-s l) "indigo" (texto-tam l))]
                            [(key=? c "f2") (make-texto (texto-s l) "blue" (texto-tam l))]
                            [(key=? c "f3") (make-texto (texto-s l) "green" (texto-tam l))]
                            [(key=? c "f4") (make-texto (texto-s l) "yellow" (texto-tam l))]
                            [(key=? c "f5") (make-texto (texto-s l) "red" (texto-tam l))]
                            [(key=? c "f6") (make-texto (texto-s l) "pink" (texto-tam l))]
                            [(key=? c "up") (make-texto (texto-s l) (texto-color l) (+ (texto-tam l) 1))]
                            [(key=? c "down") (make-texto (texto-s l) (texto-color l) (if (< 1 (- (texto-tam l) 1)) (- (texto-tam l) 1) (texto-tam l)))]
                            [else (make-texto (string-append (texto-s l) c) (texto-color l) (texto-tam l))]))
(big-bang INICIAL [to-draw escribir]
             [on-key teclado])