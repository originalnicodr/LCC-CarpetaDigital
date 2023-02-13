;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |8|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
;Representamos una frase/palabra con un string
;string-last String -> String
;Recibe una cadena de caracteres y devuelve el ultimo caracter
;(string-last "Nicolas")="s"
;(string-last "A Song of Ice and Fire")="e"
;(string-last "N")="N"
(define (string-last x) (substring x (- (string-length x) 1)))

(check-expect (string-last "Nicolas") "s")
(check-expect (string-last "A Song of Ice and Fire") "e")
(check-expect (string-last "N") "N")