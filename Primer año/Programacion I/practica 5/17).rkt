;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname |17)|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define (positivos l) (cond [(empty? l) '()]
                            [(cons? l) (if (< 0 (first l)) (cons (first l) (positivos (rest l))) (positivos (rest l)))]))

(check-expect (positivos (list -5 37 -23 0 12)) (list 37 12))