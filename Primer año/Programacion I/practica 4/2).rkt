;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |2)|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")))))
(define-struct possn [x y])
 ; una posición es (make-posn Number Number)
 ; interpretación: un elemento en posn representa una
; posición en coordenadas cartesianas

(define p (make-possn 3 4))
(define q (make-possn -2 0.5))

(check-expect (possn-x p) 3)
(check-expect (- (possn-y p) (possn-y q)) 3.5)
(check-expect (possn-y (make-possn (possn-x p) (possn-x q))) -2)

