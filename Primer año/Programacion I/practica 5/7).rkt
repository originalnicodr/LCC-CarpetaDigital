;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname |7)|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
; Una Lista-de-montos es: 
; – '()
; – (cons NumeroPositivo Lista-de-montos)
; Lista-de-montos representa una lista con montos de dinero

(define EJEMPLO (cons 50000 (list 100 200 500 1000)))

(define (sumal l) (cond [(empty? l) 0]
                        [(cons? l) (+ (first l) (sumal (rest l)))]))

(sumal EJEMPLO)