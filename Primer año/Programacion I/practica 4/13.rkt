;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname |13|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
;Una persona es: (make-persona nombre peso unidadp altura unidada)
;El primer elemento representa el nombre y apellido de la persona, el segundo su peso, el tercero la unidad del peso, el cuarto la altura y el quinto la unidad de la altura
(define-struct persona [nombre peso unidadp altura unidada])

;Represento el peso y la altura de una persona, en conjunto con las unidades de cada parametro, un una estructura "persona".
;imc: persona -> Number, String
;Toma el peso y la altura de una persona y calcula su masa corporal.
(define (imc p) (cond [(persona?? p) (/ (g->kg p) (sqr (cm->m p)))]
                       [else "Tipo de dato inválido"]))

(check-expect (imc (make-persona "Juan Navall" 150 "KG" 170 "Cms")) (/ 150 (sqr 1.7)))
(check-expect (imc (make-persona "Juan Navall" 100000 "G" 1.5 "Mts")) (/ 100 (sqr 1.5)))
(check-expect (imc (make-persona "Juan Navall" -100000 "G" 1.5 "Mts")) "Tipo de dato inválido")
(check-expect (imc (make-persona "Juan Navall" 100000 "G" 1.5 "Dm")) "Tipo de dato inválido")
(check-expect (imc "juan") "Tipo de dato inválido")

;Representa el peso de una persona con un numero y la unidad de medidad de este mediante un string.
;g-kg: persona -> Number
;Transformo el peso de gramos a kilogramos en caso de ser necesario. Si es una unidad desconocida dara un valor 0 que significara un error.
(define (g->kg p) (cond [(string=? "KG" (persona-unidadp p)) (persona-peso p)]
                        [(string=? "G" (persona-unidadp p)) (/ (persona-peso p) 1000)]
                        [else 0])) ;nunca deberia entrar aca
;Representamos la altura de una persona mediante un numero, y la unidad de meidad de esta con un string.
;cm->m: persona -> Number
;Transforma la altura de una persa de cm am en caso de ser necesario.

(define (cm->m p) (cond [(string=? "Mts" (persona-unidada p)) (persona-altura p)]
                        [(string=? "Cms" (persona-unidada p)) (/ (persona-altura p) 100)]
                        [else 0])) ;nunca deberia entrar aca

;Representamos el nombre de una persona, el peso, la altura y sus respectibas unidades en una estructura "persona"
;persona??: persona -> Boolean
;Chequea si la variable es una estructura "persona"

(define (persona?? p) (cond [(and (persona? p) (string? (persona-nombre p)) (if (number? (persona-peso p)) (< 0 (persona-peso p)) #false) (or (string=? (persona-unidadp p) "KG") (string=? (persona-unidadp p) "G")) (if (number? (persona-altura p)) (< 0 (persona-altura p)) #false) (or (string=? (persona-unidada p) "Mts") (string=? (persona-unidada p) "Cms"))) #t]
                            [else #f]))