;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname |8)|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
; Una Lista-de-montos es: 
; – '()
; – (cons NumeroPositivo Lista-de-montos)
; Lista-de-montos representa una lista con montos de dinero

(define EJEMPLO (cons 50000 (list 100 200 500 1000)))

(define (sumal l) (cond [(empty? l) 0]
                        [(cons? l) (+ (first l) (sumal (rest l)))]))

;(sumal EJEMPLO)

(define (pos? l) (cond [(empty? l) #f]
                       [(cons? l) (if (< 0 (first l)) (if (empty? (rest l)) #true (pos? (rest l))) #false)]))

(pos? EJEMPLO)

(define (checked-suma l) (if (pos? l) (sumal l) "Error, montos no positivos"))