;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname |22)|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define (sgn2 x) (cond [(< x 0) -1]
                       [(= x 0) 0]
                       [(> x 0) 1]))


(define (signos l) (cond [(empty? l) '()]
                         [(cons? l) (cons (sgn2 (first l)) (signos (rest l)))]))

(check-expect (signos (list 45 32 -23 0 12)) (list 1 1 -1 0 1))