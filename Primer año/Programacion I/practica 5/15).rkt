;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname |15)|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define (mayores n l) (cond [(empty? l) '()]
                            [(cons? l) (if (< n (first l)) (cons (first l) (mayores n (rest l))) (mayores n (rest l)))]))

(mayores 5 (list 2 7 2 4 8 1 12))