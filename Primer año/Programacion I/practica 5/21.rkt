;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname |21|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(require 2htdp/image)

(define (anchos l) (cond [(empty? l) '()]
                         ((cons? l) (cons (image-width (first l)) (anchos (rest l))))))

(check-expect (anchos (list (circle 30 "solid" "red") (rectangle 10 30 "outline" "blue"))) (list 60 10))