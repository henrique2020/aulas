;gnu clisp  2.49.60

;Calculo da hipotenusa
(print ((lambda(b c) (sqrt( + (* b b)(* c c))))3 4))

;Conversão de temperatura
(print ((lambda(f) (/ (* 5 (- f 32)) 9)) 32.0))

;Cálculo da Área de um Terreno
(print ((lambda (c1 l1 c2 l2 i) (/ (+ (* c1 l1) (* c2 l2)) i)) 14 18 22 18 3))

;Cálculo do Comprimento de um Terreno
(print ((lambda (c1 l1 c2 l2 i) (/ (+ c1 c2) i)) 14 18 22 18 3))
