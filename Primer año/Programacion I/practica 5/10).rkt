;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname |10)|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define (cat l) (cond [(empty? l) ""] ;esta bien?
                      [(cons? l) (string-append (first l) (cat (rest l)))]))
(define H (list "hola" " tarola" " todo bien?"))