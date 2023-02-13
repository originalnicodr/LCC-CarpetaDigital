;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname |4)|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
; contiene-Marcos? : Contactos -> Booleano
; dada una lista de Contactos, determina si "Marcos" es un elemento de la misma
 
(check-expect (contiene-Marcos? '()) #false)
(check-expect (contiene-Marcos? (cons "Sara" (cons "Pedro"  (cons "Esteban" '())))) #false)
(check-expect (contiene-Marcos? (cons "A" (cons "Marcos" (cons "C" '())))) #true)
(check-expect (contiene-Marcos? (cons "Juan" '())) #false)
(check-expect (contiene-Marcos? (cons "Marcos" '())) #true)
 
(define (contiene-Marcos? l) (cond [(empty? l) #false]
                                   [(cons? l) (if (string=? (first l) "Marcos")
                                                  #true
                                                  (contiene-Marcos? (rest l)))]))
(contiene-Marcos? (cons "Eugenia"
  (cons "Lucía"
    (cons "Dante"
      (cons "Federico"
        (cons "Marcos"
          (cons "Gabina"
            (cons "Laura"
              (cons "Pamela" '()))))))))
)

;5)

(define (contiene? s l) (cond [(empty? l) #false]
                              [(cons? l) (if (string=? (first l) s)
                                                  #true
                                                  (contiene? s (rest l)))]))
(contiene? "cat" (cons "Eugenia"
  (cons "Lucía"
    (cons "Dante"
      (cons "Federico"
        (cons "Marcos"
          (cons "Gabina"
            (cons "Laura"
              (cons "Pamela" '())))))))))