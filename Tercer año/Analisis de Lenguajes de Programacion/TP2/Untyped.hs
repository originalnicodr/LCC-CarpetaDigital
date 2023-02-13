module Untyped where

import Control.Monad
import Data.List

import Common


----------------------------------------------
-- Seccón 2 - Representación de Términos Lambda
-- Ejercicio 2: Conversión de Términos
----------------------------------------------

variable :: String -> NameEnv Int -> Term
variable a [] = Free a
variable a ((x,y):xs) = if a==x then (Bound y) else (variable a xs)

update_v :: String -> NameEnv Int -> Int -> [(String,Int)]
update_v a [] n = [(a,n)]
update_v a ((x,y):xs) n = if a==x then ((x,n):xs) else ((x,y):(update_v a xs n))

conversion' :: LamTerm -> NameEnv Int -> Int -> Term
conversion' (LVar s) xs n = variable s xs
conversion' (App t1 t2) xs n = (conversion' t1 xs n) :@: (conversion' t2 xs n)
conversion' (Abs s t) xs n = Lam (conversion' t (update_v s xs n) (n+1))

conversion  :: LamTerm -> Term
conversion t = conversion' t [] 0

-------------------------------
-- Sección 3 - Evaluación
-------------------------------

shift :: Term -> Int -> Int -> Term
shift (Free a) c d = (Free a)
shift (Bound x) c d = if (x<c) then (Bound x) else (Bound (x+d))
shift (t1 :@: t2) c d = (shift t1 c d) :@: (shift t2 c d)
shift (Lam t) c d = Lam (shift t c d)

subst' :: Term -> Term -> Int -> Int -> Term
subst' (Free a) t i j = (Free a)
subst' (Bound x) t i j = if (x==i) then (shift t i j)
                                   else if (x<i) then (Bound x)
                                                 else (Bound (x-1))
subst' (t1 :@: t2) t i j = (subst' t1 t i j) :@: (subst' t2 t i j)
subst' (Lam t1) t i j = Lam (subst' t1 t i (j+1))

subst :: Term -> Term -> Int -> Term
subst t t' i = subst' t t' i 0


beta_red :: Term -> Int -> Term
beta_red ((Lam t) :@: t') j = subst t t' j
beta_red x j = x

-- No ponemos el caso de la vacia ya que suponemos que las variables globales estan siempre
lookfor :: NameEnv Term -> String -> Maybe Term
lookfor [] s = Nothing
lookfor ((x,t):xs) s = if (x==s) then (Just t) else (lookfor xs s)

-- se rompe si el infinito no es igual
eval' :: NameEnv Term -> Term -> Int -> Term
eval' xs (Free a) j = let res = lookfor xs a
                      in case res of
                          Nothing -> Free a
                          Just t -> eval' xs (shift t 0 j) j
eval' xs (Bound x) j = Bound x
eval' xs ((Lam t1) :@: t2) j = (eval' xs (subst t1 t2 j) j)--E-AppAbs
eval' xs (t1 :@: t2) j = let res = eval' xs t1 j
                         in case res of
                           Lam t' -> eval' xs (res :@: (eval' xs t2 j)) j
                           x -> res :@: (eval' xs t2 j)
eval' xs (Lam t) j = Lam (eval' xs t (j+1))


eval :: NameEnv Term -> Term -> Term
eval xs t = eval' xs t 0
