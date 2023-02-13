;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |8|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")))))
;Representamos una frase/palabra mediante una cadena de caracteres
;string-remove-last String -> String
;Recibe una cadena de caracteres y devuelve la misma cadena sin el ultimo caracter
;(string-remove-last "La respusta al universo, la vida y todo es 42")="La respusta al universo, la vida y todo es 4"
;(string-remove-last "Q")=""
;(string-remove-last "Master Race") "Master Rac"

(define (string-remove-last s) (if (not (= 0 (string-length s))) (substring s 0 (- (string-length s) 1)) "Ingrese una palabra no vacia"))

(check-expect (string-remove-last "La respusta al universo, la vida y todo es 42") "La respusta al universo, la vida y todo es 4")
(check-expect (string-remove-last "Q") "")
(check-expect (string-remove-last "Master Race") "Master Rac")