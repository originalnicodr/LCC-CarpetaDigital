;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname banderas) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(require 2htdp/image)
(define ejemplo (place-image (rectangle 90 30 "solid" "red") 45 15
                             (place-image (circle 10 "solid" "blue") 45 45
                                          (empty-scene 90 60))))
(define paloma (place-image (rectangle 30 60 "solid" "red") 15 30
                             (place-image (rectangle 30 60 "solid" "red") 75 30
                                          (empty-scene 90 60))))

(define pasta (place-image (rectangle 30 60 "solid" "green") 15 30
                             (place-image (rectangle 30 60 "solid" "red") 75 30
                                          (empty-scene 90 60))))

(define (bandera1 a b c) (place-image (rectangle 30 60 "solid" a) 15 30
                             (place-image (rectangle 30 60 "solid" b) 45 30
                             (place-image (rectangle 30 60 "solid" c) 75 30
                                          (empty-scene 90 60)))))
(define NAIN (place-image (rectangle 90 20 "solid" "black") 45 10
              (place-image (rectangle 90 20 "solid" "red") 45 30
                           (place-image (rectangle 90 20 "solid" "yellow") 45 50
                                          (empty-scene 90 60)))))
(define Holanda (place-image (rectangle 90 20 "solid" "red") 45 10
              (place-image (rectangle 90 20 "solid" "white") 45 30
                           (place-image (rectangle 90 20 "solid" "blue") 45 50
                                          (empty-scene 90 60)))))

(define (bandera2 a b c) (place-image (rectangle 90 20 "solid" a) 45 10
              (place-image (rectangle 90 20 "solid" b) 45 30
                           (place-image (rectangle 90 20 "solid" c) 45 50
                                          (empty-scene 90 60)))))
(define (bandera3 a b c d) (if (string=? d "horizontal") (bandera2 a b c) (if (string=? d "vertical") (bandera1 a b c) "Ingrese un sentido correcto")))

;(bandera3 "red" "white" "blue" "vertical")

(define sudan (overlay/xy (rotate 90 (triangle 60 "solid" "green")) 30 25
              (bandera3 "red" "white" "blue" "horizontal")))

(define argentina (overlay/xy (circle 9 "solid" "yellow") -36 -21
              (bandera3 "blue" "white" "blue" "horizontal")))

(define camerun (overlay/xy (star 10 "solid" "yellow") -36 -21
              (bandera3 "green" "red" "yellow" "vertical")))

(define brazil             (place-image (circle 13 "solid" "blue") 45 30
                           (place-image (rotate 90 (triangle 45 "solid" "yellow")) 25 30
                           (place-image (rotate 270 (triangle 45 "solid" "yellow")) 65 30
                           (place-image (rectangle 90 60 "solid" "green") 45 30

                                          (empty-scene 90 60))))))

brazil