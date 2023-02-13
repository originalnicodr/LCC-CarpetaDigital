;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname |13)|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define (pares l) (cond [(empty? l) '()]
                        [(cons? l) (if (even? (first l)) (cons (first l) (pares (rest l))) (pares (rest l)))]))

(pares (list 2 4 7 1 6 2))