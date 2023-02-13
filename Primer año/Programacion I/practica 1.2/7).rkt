;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |7)|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(require 2htdp/image)

(define (l-g-c x) (cond [ (> (image-width x) (image-height x)) "Gorda"]
                        [ (= (image-width x) (image-height x)) "Cuadrada"]
                        [ else "Alta"]
                        ))

(define (sgn2 x) (cond [(boolean? x) (if x 1 0)]
                       [(image? x) (if (string=? (l-g-c x) "Gorda") 1 (if (string=? (l-g-c x) "Alta") -1 0))]
                       [(< x 0) -1]
                       [(= x 0) 0]
                       [(> x 0) 1]))
