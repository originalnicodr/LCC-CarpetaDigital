module Eval1 (eval) where

import AST
import Control.Applicative (Applicative(..))
import Control.Monad       (liftM, ap)

-- Estados
type Env = [(Variable,Int)]

-- Estado nulo
initState :: Env
initState = []

-- Mónada estado
newtype State a = State { runState :: Env -> (a, Env) }

instance Monad State where
    return x = State (\s -> (x, s))
    m >>= f = State (\s -> let (v, s') = runState m s in
                           runState (f v) s')

-- Para calmar al GHC
instance Functor State where
    fmap = liftM

instance Applicative State where
    pure   = return
    (<*>)  = ap

-- Clase para representar mónadas con estado de variables
class Monad m => MonadState m where
    -- Busca el valor de una variable
    lookfor :: Variable -> m Int
    -- Cambia el valor de una variable
    update :: Variable -> Int -> m ()

instance MonadState State where
    lookfor v = State (\s -> (lookfor' v s, s))
                where lookfor' v ((u, j):ss) | v == u = j
                                             | v /= u = lookfor' v ss
    update v i = State (\s -> ((), update' v i s))
                 where update' v i [] = [(v, i)]
                       update' v i ((u, _):ss) | v == u = (v, i):ss
                       update' v i ((u, j):ss) | v /= u = (u, j):(update' v i ss)


-- Evalua un programa en el estado nulo
eval :: Comm -> Env
eval p = snd (runState (evalComm p) initState)

-- Evalua un comando en un estado dado
evalComm :: MonadState m => Comm -> m ()
evalComm (Let v n) = do n' <- evalIntExp n
                        update v n'
evalComm (Seq c1 c2)= do evalComm c1
                         evalComm c2
evalComm (IfThenElse b c1 c2)= do b'<- evalBoolExp b
                                  if b' then evalComm c1
                                        else evalComm c2
evalComm (While b c)= do b'<- evalBoolExp b
                         if b' then evalComm (Seq c (While b c))
                               else return ()


-- Evalua una expresion entera en un estado dado
evalIntExp :: MonadState m => IntExp -> m Int
evalIntExp (Const c)= return c
evalIntExp (Var v)= lookfor v
evalIntExp (UMinus v)= do n <- evalIntExp v
                          return (-n)
evalIntExp (Plus m n)= do m' <- evalIntExp m
                          n' <- evalIntExp n
                          return (m'+n')
evalIntExp (Minus m n)= do m' <- evalIntExp m
                           n' <- evalIntExp n
                           return (m'-n')
evalIntExp (Times m n)= do m' <- evalIntExp m
                           n' <- evalIntExp n
                           return (m'*n')
evalIntExp (Div m n)= do m' <- evalIntExp m
                         n' <- evalIntExp n
                         return (div m' n')
evalIntExp (Ass v n)= do n' <- evalIntExp n
                         update v n'
                         return n'
evalIntExp (SeqIE m n)= do m' <- evalIntExp m
                           n' <- evalIntExp n
                           return n'

-- Evalua una expresion booleana en un estado dado
evalBoolExp :: MonadState m => BoolExp -> m Bool
evalBoolExp BTrue = return True
evalBoolExp BFalse = return False
evalBoolExp (Eq a b)= do a' <- evalIntExp a
                         b' <- evalIntExp b
                         return (a' == b')
evalBoolExp (NEq a b)= do a' <- evalIntExp a
                          b' <- evalIntExp b
                          return (a' /= b')
evalBoolExp (Lt a b)= do a' <- evalIntExp a
                         b' <- evalIntExp b
                         return (a' < b')
evalBoolExp (Gt a b)= do a' <- evalIntExp a
                         b' <- evalIntExp b
                         return (a' > b')
evalBoolExp (And a b)= do a' <- evalBoolExp a
                          b' <- evalBoolExp b
                          return (a' && b')
evalBoolExp (Or a b)= do a' <- evalBoolExp a
                         b' <- evalBoolExp b
                         return (a' || b')
evalBoolExp (Not b)= do b' <- evalBoolExp b
                        return (not b')
