;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname |11)|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define (cant-elementos l) (cond [(empty? l) 0]
                                 [(cons? l) (+ 1 (cant-elementos (rest l)))]))

(cant-elementos (list 2 7 1 "aldgbhn" #t))