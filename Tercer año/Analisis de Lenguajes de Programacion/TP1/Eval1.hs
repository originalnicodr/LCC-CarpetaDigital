module Eval1 (eval) where

import AST

-- Estados
type State = [(Variable,Integer)]

-- Estado nulo
initState :: State
initState = []

-- Busca el valor de una variabl en un estado
-- Completar la definicion
lookfor :: Variable -> State -> Integer
lookfor v ((x,y):xs) | v==x = y
                                 | otherwise = lookfor v xs

-- Cambia el valor de una variable en un estado
-- Completar la definicion
update :: Variable -> Integer -> State -> State
update v i [] = [(v,i)]
update v i ((x,y):xs) | v==x = (v,i):xs
                      | otherwise = (x,y):(update v i xs)

-- Evalua un programa en el estado nulo
eval :: Comm -> State
eval p = evalComm p initState

-- Evalua un comando en un estado dado
-- Completar definicion
evalComm :: Comm -> State -> State
evalComm Skip s = s
evalComm (LetC v e) s = update v (evalIntExp e s) s
evalComm (Seq c1 c2) s = evalComm c2 (evalComm c1 s)
evalComm (IfThenElse b c1 c2) s = if (evalBoolExp b s)
                                    then evalComm c1 s
                                    else evalComm c2 s
evalComm (While b c) s = if (evalBoolExp b s)
                           then evalComm (While b c) (evalComm c s)
                           else s

-- Evalua una expresion entera, sin efectos laterales
-- Completar definicion
evalIntExp :: IntExp -> State -> Integer
evalIntExp (Const i) s = i
evalIntExp (Var v) s = lookfor v s
evalIntExp (UMinus e) s = -(evalIntExp e s)
evalIntExp (Plus e1 e2) s = (evalIntExp e1 s) + (evalIntExp e2 s)
evalIntExp (Minus e1 e2) s = (evalIntExp e1 s) - (evalIntExp e2 s)
evalIntExp (Times e1 e2) s = (evalIntExp e1 s) * (evalIntExp e2 s)
evalIntExp (Div e1 e2) s = div (evalIntExp e1 s) (evalIntExp e2 s)


-- Evalua una expresion entera, sin efectos laterales
-- Completar definicion
evalBoolExp :: BoolExp -> State -> Bool
evalBoolExp BTrue s = True
evalBoolExp BFalse s = False
evalBoolExp (Eq e1 e2) s = (evalIntExp e1 s) == (evalIntExp e2 s)
evalBoolExp (NEq e1 e2) s = (evalIntExp e1 s) /= (evalIntExp e2 s)
evalBoolExp (Lt e1 e2) s = (evalIntExp e1 s) < (evalIntExp e2 s)
evalBoolExp (Gt e1 e2) s = (evalIntExp e1 s) > (evalIntExp e2 s)
evalBoolExp (And b1 b2) s = (evalBoolExp b1 s) && (evalBoolExp b2 s)
evalBoolExp (Or b1 b2) s = (evalBoolExp b1 s) || (evalBoolExp b2 s)
evalBoolExp (Not b) s = not (evalBoolExp b s)
