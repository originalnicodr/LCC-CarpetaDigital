;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |10)|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(require 2htdp/image)

(define (tipo? x) (cond [(string? x) "Es una string."]
                        [(number? x) "Es un numero."]
                        [(boolean? x) "Es un booleano."]
                        [(image? x) "Es una imagen."]))