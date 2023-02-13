;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname |14)|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define (cortas l) (cond [(empty? l) '()]
                         [(cons? l) (if (> 5 (string-length (first l))) (cons (first l) (cortas (rest l))) (cortas (rest l)))]))

(cortas (list "hola" "holas" "qsy" "nose" "xdddd"))