;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |6|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")))))
;Representamos una/s palabra/s con un string y una posicion con un numero
;string-insert String Number -> String
;Recibe serie de caracteres y un numero, y devuelve la misma palabra con un guion instertado en la posicion indicada
;(string-insert "Hola" 2)="Ho-la"
;(string-insert "LCC" 0)="-LCC"
;(string-insert "Winter is coming" (/ (string-length "Winter is coming") 2))="Winter i-s coming"


(define (string-insert s i) (if (<= i (string-length s)) (string-append (substring s 0 i) "-" (substring s i (string-length s))) "Ingrese una posicion posible"))
(check-expect(string-insert "Hola" 2) "Ho-la")
(check-expect(string-insert "LCC" 0) "-LCC")
(check-expect(string-insert "Winter is coming" (/ (string-length "Winter is coming") 2)) "Winter i-s coming")