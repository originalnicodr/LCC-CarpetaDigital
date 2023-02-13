;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |ej 2)|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))
;a)
(/ 1 (sin (sqrt 3)))
;b)
    (* (sqrt 2) (sin pi))
;c)
    (+ 3 (sqrt (- 4)))
;d)
    (* (sqrt 5) (sqrt (/ 3 (cos pi))))
;e)
    ;(/ (sqrt 5) (sin (* 3 0)))
    ;Error: Divide por cero
;f)
    ;(/ (+ 3) (* 2 4))
    ;Error: Expresion mal escrita. Correccion sugerida
    (/ 3 (* 2 4))
;g)
    (* 1 2 3 4 5 6 7 8)
;h)
    (/ 120 2 3 2 2 5)