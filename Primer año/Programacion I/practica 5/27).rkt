;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname |27)|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define (pegar l) (cond [(empty? l) ""]
                        [(cons? l) (string-append (first l) (pegar (rest l)))]))

(check-expect (pegar (list "Las " "lis" "tas " "son " "complicadas" ".")) "Las listas son complicadas.")