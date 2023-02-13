;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname |24)|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define (longitudes l) (cond [(empty? l) '()]
                             [(cons? l) (cons (string-length (first l)) (longitudes (rest l)))]))

(check-expect (longitudes(list "hola" "cómo" "estás?")) (list 4 4 6))