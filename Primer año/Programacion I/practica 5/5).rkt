;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname |5)|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
; contiene-Marcos? : String List -> Booleano
; dada un string, determina si la cadena es un elemento de la misma

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