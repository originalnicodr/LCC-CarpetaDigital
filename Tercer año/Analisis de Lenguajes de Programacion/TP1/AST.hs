module AST where

-- Identificadores de Variable
type Variable = String

-- Expresiones Aritmeticas
data IntExp = Const Integer
            | Var Variable
            | LetI Variable IntExp
            | UMinus IntExp
            | Plus IntExp IntExp
            | Minus IntExp IntExp
            | Times IntExp IntExp
            | Div IntExp IntExp
            | Coma IntExp IntExp
 deriving Show

-- Expresiones Booleanas
data BoolExp = BTrue
             | BFalse
             | Eq IntExp IntExp
             | NEq IntExp IntExp
             | Lt IntExp IntExp
             | Gt IntExp IntExp
             | And BoolExp BoolExp
             | Or BoolExp BoolExp
             | Not BoolExp
 deriving Show

-- Comandos (sentencias)
-- Observar que solo se permiten variables de un tipo (entero)
data Comm = Skip
          | LetC Variable IntExp
          | Seq Comm Comm
	      | IfThenElse BoolExp Comm Comm -- El IfThen podes hacer con un Skip en el segundo comando
          | While BoolExp Comm
 deriving Show
