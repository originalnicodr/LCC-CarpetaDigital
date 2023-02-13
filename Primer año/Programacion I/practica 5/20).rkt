;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname |20)|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define (distanciaxy x y) (sqrt (+ (sqr x) (sqr y))))

(define-struct possn [x y])
 ; una posición es (make-posn Number Number)
 ; interpretación: un elemento en posn representa una
; posición en coordenadas cartesianas

(define (distancias l) (cond [(empty? l) '()]
                             [(cons? l) (cons (distanciaxy (possn-x (first l)) (possn-y (first l))) (distancias (rest l)))]))

(check-expect (distancias (list (make-possn 3 4) (make-possn 0 4) (make-possn 12 5))) (list 5 4 13))