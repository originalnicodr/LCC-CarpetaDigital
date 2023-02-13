;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname |26)|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define (prod l) (cond [(empty? l) 1]
                       [(cons? l) (* (first l) (prod (rest l)))]))

(check-expect (prod (list 1 2 3 4 5)) 120)