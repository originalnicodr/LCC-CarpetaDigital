module Eval3 (eval) where

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
eval :: Comm -> Either Error (State, Int)
eval p = let (s, n) = evalComm p initState 0
         in case s of
             Left x -> Left x
             Right x -> Right (x, n)

-- Cuando da error no dice el costo

-- Evalua un comando en un estado dado
-- Completar definicion
evalComm :: Comm -> State -> Int -> (Either Error State, Int)
evalComm Skip s n = (Right s, n)
evalComm (LetC v e) s n = let (res1, n1) = (evalIntExp e s)
                          in case res1 of
                              Left x -> (Left x, n+n1)
                              Right x -> (Right (update v x s), n+n1)
evalComm (Seq c1 c2) s n = let (res1, n1) = evalComm c1 s n
                           in case res1 of
                               Left x -> (Left x, n1)
                               Right x -> evalComm c2 x n1
evalComm (IfThenElse b c1 c2) s n = let (res1, n1) = evalBoolExp b s
                                    in case res1 of
                                         Left x -> (Left x, n)
                                         Right x -> if x
                                                then evalComm c1 s (n+n1)
                                                else evalComm c2 s (n+n1)
evalComm (While b c) s n = let (res1, n1) = (evalBoolExp b s)
                           in case res1 of
                               Left x -> (Left x, n+n1)
                               Right x -> if x
                                            then evalComm (Seq c (While b c)) s (n+n1)
                                            else (Right s, n+n1)

-- Evalua una expresion entera, sin efectos laterales
-- Completar definicion
evalIntExp :: IntExp -> State -> (Either Error Integer, Int)
evalIntExp (Const i) s = (Right i, 0)
evalIntExp (Var v) s = (lookfor v s, 0)
evalIntExp (UMinus e) s = let (res, n) = evalIntExp e s
                          in (catcherU res (0-), n+1)
evalIntExp (Plus e1 e2) s = let (res1, n1) = evalIntExp e1 s
                                (res2, n2) = evalIntExp e2 s
                            in (catcherBin res1 res2 (+), 1+n1+n2)
evalIntExp (Minus e1 e2) s = let (res1, n1) = evalIntExp e1 s
                                 (res2, n2) = evalIntExp e2 s
                             in (catcherBin res1 res2 (-), 1+n1+n2)
evalIntExp (Times e1 e2) s = let (res1, n1) = evalIntExp e1 s
                                 (res2, n2) = evalIntExp e2 s
                             in (catcherBin res1 res2 (*), 2+n1+n2)
evalIntExp (Div e1 e2) s =  let (res1, n1) = evalIntExp e1 s
                                (res2, n2) = evalIntExp e2 s
                            in (catcherDiv res1 res2, 2+n1+n2)


-- Evalua una expresion entera, sin efectos laterales
-- Completar definicion
evalBoolExp :: BoolExp -> State -> (Either Error Bool, Int)
evalBoolExp BTrue s = (Right True, 0)
evalBoolExp BFalse s = (Right False, 0)
evalBoolExp (Eq e1 e2) s = let (res1, n1) = evalIntExp e1 s
                               (res2, n2) = evalIntExp e2 s
                           in (catcherBin res1 res2 (==), 1+n1+n2)
evalBoolExp (NEq e1 e2) s = let (res1, n1) = evalIntExp e1 s
                                (res2, n2) = evalIntExp e2 s
                            in (catcherBin res1 res2 (/=), 1+n1+n2)
evalBoolExp (Lt e1 e2) s = let (res1, n1) = evalIntExp e1 s
                               (res2, n2) = evalIntExp e2 s
                           in (catcherBin res1 res2 (<), 1+n1+n2)
evalBoolExp (Gt e1 e2) s = let (res1, n1) = evalIntExp e1 s
                               (res2, n2) = evalIntExp e2 s
                           in (catcherBin res1 res2 (>), 1+n1+n2)
evalBoolExp (And b1 b2) s = let (res1, n1) = evalBoolExp b1 s
                                (res2, n2) = evalBoolExp b2 s
                            in (catcherBin res1 res2 (&&), 1+n1+n2)
evalBoolExp (Or b1 b2) s = let (res1, n1) = evalBoolExp b1 s
                               (res2, n2) = evalBoolExp b2 s
                           in (catcherBin res1 res2 (||), 1+n1+n2)
evalBoolExp (Not b) s = let (res, n) = evalBoolExp b s
                        in (catcherU res not, n+1)
