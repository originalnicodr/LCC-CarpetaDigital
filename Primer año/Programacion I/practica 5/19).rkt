;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname |19)|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define (raices l) (cond [(empty? l) '()]
                         [(cons? l) (cons (sqrt (first l)) (raices (rest l)))]))

(check-expect (raices (list 9 16 4)) (list 3 4 2))