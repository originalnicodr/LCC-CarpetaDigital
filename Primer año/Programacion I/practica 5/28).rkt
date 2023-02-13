;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname |28)|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define (maximo l) (cond [(empty? l) 0]
                      [(cons? l) (if (and (> (first l) 0 ) (> (first l) (maximo (rest l)))) (first l) (maximo (rest l)))]))

(check-expect (maximo (list 23 543 325 0 75)) 543)