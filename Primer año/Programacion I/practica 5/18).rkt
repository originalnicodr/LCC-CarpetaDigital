;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname |18)|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define (eliminar n l) (cond [(empty? l) '()]
                             [(cons? l) (if (= n (first l)) (eliminar n (rest l)) (cons (first l) (eliminar n (rest l))))]))

(check-expect (eliminar 2 (list 1 2 3 2 7 6)) (list 1 3 7 6))
 
(check-expect (eliminar 0 (list 1 2 3 2 7 6)) (list 1 2 3 2 7 6))