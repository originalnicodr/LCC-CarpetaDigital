module Eval2 (eval) where

import AST
import Control.Applicative (Applicative(..))
import Control.Monad       (liftM, ap)

-- Estados
type Env = [(Variable,Int)]

-- Estado nulo
initState :: Env
initState = []

-- Mónada estado, con manejo de errores
newtype StateError a = StateError { runStateError :: Env -> Maybe (a, Env) }

-- Para calmar al GHC
instance Functor StateError where
    fmap = liftM

instance Applicative StateError where
    pure   = return
    (<*>)  = ap

-- Clase para representar mónadas con estado de variables
class Monad m => MonadState m where
    -- Busca el valor de una variable
    lookfor :: Variable -> m Int
    -- Cambia el valor de una variable
    update :: Variable -> Int -> m ()

-- Clase para representar mónadas que lanzan errores
class Monad m => MonadError m where
    -- Lanza un error
    throw :: m a

instance Monad StateError where
  return x = StateError (\s-> Just (x,s))
  StateError g >>= f = StateError (\s-> case (g s) of
                                          Nothing -> Nothing
                                          Just (a,s') -> runStateError (f a) s')

instance MonadError StateError where
  throw = StateError (\_ -> Nothing)

instance MonadState StateError where
  lookfor v = StateError (\s -> case lookfor' v s of
                                  Nothing -> Nothing
                                  Just n -> Just (n, s))
              where lookfor' v [] = Nothing
                    lookfor' v ((u, j):ss) | v == u = Just j
                                           | v /= u = lookfor' v ss
  update v i = StateError (\s -> Just ((), update' v i s))
               where update' v i [] = [(v, i)]
                     update' v i ((u, _):ss) | v == u = (v, i):ss
                     update' v i ((u, j):ss) | v /= u = (u, j):(update' v i ss)


-- Evalua un programa en el estado nulo
eval :: Comm -> Maybe Env
eval p = case (runStateError (evalComm p) initState) of
           Nothing -> Nothing
           Just (a, s) -> Just s

-- Evalua un comando en un estado dado
evalComm :: (MonadState m, MonadError m) => Comm -> m ()
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
evalIntExp :: (MonadState m, MonadError m) => IntExp -> m Int
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
                         if (n'==0) then throw
                                    else return (div m' n')
evalIntExp (Ass v n)= do n' <- evalIntExp n
                         update v n'
                         return n'
evalIntExp (SeqIE m n)= do m' <- evalIntExp m
                           n' <- evalIntExp n
                           return n'

-- Evalua una expresion booleana en un estado dado
evalBoolExp :: (MonadState m, MonadError m) => BoolExp -> m Bool
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
