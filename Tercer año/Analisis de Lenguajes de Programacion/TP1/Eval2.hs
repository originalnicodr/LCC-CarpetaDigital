module Eval2 (eval) where

import AST

-- Estados
type State = [(Variable,Integer)]

data Error = DivByZero | UndefVar
            deriving Show

-- Estado nulo
initState :: State
initState = []

-- Busca el valor de una variabl en un estado
-- Completar la definicion
lookfor :: Variable -> State -> Either Error Integer
lookfor v [] = Left UndefVar
lookfor v ((x,y):xs) | v==x = Right y
                     | otherwise = lookfor v xs

-- Cambia el valor de una variable en un estado
-- Completar la definicion
update :: Variable -> Integer -> State -> State
update v i [] = [(v,i)]
update v i ((x,y):xs) | v==x = (v,i):xs
                      | otherwise = (x,y):(update v i xs)


catcherDiv :: Either Error Integer -> Either Error Integer -> Either Error Integer
catcherDiv (Right x1) (Right 0) = Left DivByZero
catcherDiv x1 x2 = catcherBin x1 x2 div

catcherBin :: Either Error a -> Either Error a -> (a -> a -> b) -> Either Error b
catcherBin (Right x1) (Right x2) op = Right (op x1 x2)
catcherBin (Left x) _ _ = Left x
catcherBin _ (Left x) _ = Left x

catcherU :: Either Error a -> (a -> a) -> Either Error a
catcherU (Right x) op  = Right (op x)
catcherU (Left x) _ = Left x

-- Evalua un programa en el estado nulo
eval :: Comm -> Either Error State
eval p = evalComm p initState

-- Evalua un comando en un estado dado
-- Completar definicion
evalComm :: Comm -> State -> Either Error State
evalComm Skip s = Right s
evalComm (LetC v e) s = let res= (evalIntExp e s)
                        in case res of
                            Left x -> Left x
                            Right x -> Right (update v x s)
evalComm (Seq c1 c2) s = let res1=evalComm c1 s
                             in case res1 of
                                 Left x -> Left x
                                 Right x -> evalComm c2 x
evalComm (IfThenElse b c1 c2) s = let res = evalBoolExp b s
                                  in case res of
                                   Left x -> Left x
                                   Right x -> if x
                                                then evalComm c1 s
                                                else evalComm c2 s
evalComm (While b c) s = let res = (evalBoolExp b s)
                         in case res of
                             Left x -> Left x
                             Right x -> if x
                                          then evalComm (Seq c (While b c)) s
                                          else Right s

-- Evalua una expresion entera, sin efectos laterales
-- Completar definicion
evalIntExp :: IntExp -> State -> Either Error Integer
evalIntExp (Const i) s = Right i
evalIntExp (Var v) s = lookfor v s
evalIntExp (UMinus e) s = catcherU (evalIntExp e s) (0-)
evalIntExp (Plus e1 e2) s = catcherBin (evalIntExp e1 s) (evalIntExp e2 s) (+)
evalIntExp (Minus e1 e2) s = catcherBin (evalIntExp e1 s) (evalIntExp e2 s) (-)
evalIntExp (Times e1 e2) s = catcherBin (evalIntExp e1 s) (evalIntExp e2 s) (*)
evalIntExp (Div e1 e2) s =  catcherDiv (evalIntExp e1 s) (evalIntExp e2 s)


-- Evalua una expresion entera, sin efectos laterales
-- Completar definicion
evalBoolExp :: BoolExp -> State -> Either Error Bool
evalBoolExp BTrue s = Right True
evalBoolExp BFalse s = Right False
evalBoolExp (Eq e1 e2) s = catcherBin (evalIntExp e1 s) (evalIntExp e2 s) (==)
evalBoolExp (NEq e1 e2) s = catcherBin (evalIntExp e1 s) (evalIntExp e2 s) (/=)
evalBoolExp (Lt e1 e2) s = catcherBin (evalIntExp e1 s) (evalIntExp e2 s) (<)
evalBoolExp (Gt e1 e2) s = catcherBin (evalIntExp e1 s) (evalIntExp e2 s) (>)
evalBoolExp (And b1 b2) s = catcherBin (evalBoolExp b1 s) (evalBoolExp b2 s) (&&)
evalBoolExp (Or b1 b2) s = catcherBin (evalBoolExp b1 s) (evalBoolExp b2 s) (||)
evalBoolExp (Not b) s = catcherU (evalBoolExp b s) not
