;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname |30)|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define (sumcuad l) (cond [(empty? l) 0]
                          [(cons? l) [+ (sqr (first l)) (sumcuad (rest l))]]))

(check-expect (sumcuad (list 1 2 3)) 14)