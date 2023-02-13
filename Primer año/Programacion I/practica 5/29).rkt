;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname |29)|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define (distanciaxy x y) (sqrt (+ (sqr x) (sqr y))))

(define-struct possn [x y])
 ; una posición es (make-posn Number Number)
 ; interpretación: un elemento en posn representa una
; posición en coordenadas cartesianas

(define (sumdist l) (cond [(empty? l) 0]
                          [(cons? l) (+ (distanciaxy (possn-x (first l)) (possn-y (first l))) (sumdist (rest l)))]))

(check-expect (sumdist (list (make-possn 3 4) (make-possn 0 4) (make-possn 12 5))) 22)