;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname |16)|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define (distanciaxy x y) (sqrt (+ (sqr x) (sqr y))))

(define-struct possn [x y])
 ; una posición es (make-posn Number Number)
 ; interpretación: un elemento en posn representa una
; posición en coordenadas cartesianas

(define p (make-possn 3 4))
(define q (make-possn -2 0.5))

(check-expect (possn-x p) 3)
(check-expect (- (possn-y p) (possn-y q)) 3.5)
(check-expect (possn-y (make-possn (possn-x p) (possn-x q))) -2)

(list p q)

(define MAX 5)

(define (cerca l) (cond [(empty? l) '()]
                        [(cons? l) (if (> MAX (distanciaxy (possn-x (first l)) (possn-y (first l)))) (cons (first l) (cerca (rest l))) (cerca (rest l)))]))

(check-expect (cerca (list (make-possn 3 5) (make-possn 1 2) (make-possn 0 1) (make-possn 5 6))) (list (make-possn 1 2) (make-possn 0 1)))