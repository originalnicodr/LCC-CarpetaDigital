;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname |25)|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define (far->cel f) (* 5/9 (- f 32)))

(define (convertirFC l) (cond [(empty? l) '()]
                              [(cons? l) (cons (far->cel (first l)) (convertirFC (rest l)))]))