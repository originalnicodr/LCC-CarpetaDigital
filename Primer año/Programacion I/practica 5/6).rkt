;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname |6)|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
; contiene-Marcos? : Contactos -> Booleano
; dada una lista de Contactos, determina si "Marcos" es un elemento de la misma
(define (contiene-Marcos? l) (cond [(empty? l) #false]
                                   [(cons? l) (if (string=? (first l) "Marcos")
                                                  #true
                                                  (contiene-Marcos? (rest l)))]))
;(contiene-Marcos? (cons "Marcos" (cons "C" '())))
(contiene-Marcos? (cons "A" (cons "Marcos" (cons "C" '()))))