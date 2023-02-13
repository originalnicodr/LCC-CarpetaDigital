module Parser where

import Text.ParserCombinators.Parsec
import Text.Parsec.Token
import Text.Parsec.Language (emptyDef)
import AST

-----------------------
-- Funcion para facilitar el testing del parser.
totParser :: Parser a -> Parser a
totParser p = do
                  whiteSpace lis
                  t <- p
                  eof --Verifica que no queda nada en el parser
                  return t

-- Analizador de Tokens
lis :: TokenParser u
lis = makeTokenParser (emptyDef   { commentStart  = "/*"
                                  , commentEnd    = "*/"
                                  , commentLine   = "//"
                                  , opLetter      = char '='
                                  , reservedNames = ["true","false","if","then",
                                                     "else", "while", "skip"]
                                  , reservedOpNames = ["+","-","=","-","*","/","!","(",")","{","}"]

                                  })

----------------------------------
--- Parser de expressiones enteras
-----------------------------------
--{-
intexp :: Parser IntExp

intexp = chainl1 intexp1 (do reservedOp lis ","
                             return Coma)

intexp1  = chainl1 intexp2 (do reservedOp lis "+"
                               return Plus
                            <|> do reservedOp lis "-"
                                   return Minus)

intexp2 = chainl1 intexpB (do reservedOp lis "*"
                              return Times
                           <|> do reservedOp lis "/"
                                  return Div)

--Parse parser [] string

intexpB = try (do x <- natural lis
                  return (Const x))
          <|> try (do x <- identifier lis
                      (try (do reservedOp lis "="
                               e <- intexp1
                               return (LetI x e))
                       <|> return (Var x)))
              <|> do reservedOp lis "-"
                     x <- intexpB
                     return (UMinus x)
                  <|> do reservedOp lis "("
                         x <- intexp
                         reservedOp lis ")"
                         return x
--}
-----------------------------------
--- Parser de expressiones booleanas
------------------------------------

boolexp :: Parser BoolExp
boolexp = chainl1 boolexp' (do reservedOp lis "||"
                               return Or)

boolexp' = chainl1 boolexpB (do reservedOp lis "&&"
                                return And)

boolexpB = try (boolInt)
           <|> do reservedOp lis "!"
                  b <- boolexp
                  return (Not b)
               <|> do reservedOp lis "("
                      b <- boolexp
                      reservedOp lis ")"
                      return b
                   <|> do reserved lis "true"
                          return BTrue
                       <|> do reserved lis "false"
                              return BFalse


boolInt = do e1 <- intexp
             o <- (do reservedOp lis "=="
                      return Eq
                   <|> do reservedOp lis "!="
                          return NEq
                       <|> do reservedOp lis "<"
                              return Lt
                           <|> do reservedOp lis ">"
                                  return Gt)
             e2 <- intexp
             return (o e1 e2)

-----------------------------------
--- Parser de comandos
-----------------------------------

comm :: Parser Comm
comm = chainl1 commB (do reservedOp lis ";"
                         return (Seq))


commB = do reserved lis "if"
           b <- boolexp
           reservedOp lis "{"
           c <- comm
           reservedOp lis "}"
           (do reserved lis "else"
               reservedOp lis "{"
               c2 <- comm
               reservedOp lis "}"
               return (IfThenElse b c c2))
            <|> return (IfThenElse b c Skip)
        <|> do reserved lis "while"
               b <- boolexp
               reservedOp lis "{"
               c <- comm
               reservedOp lis "}"
               return (While b c)
            <|> do reserved lis "skip"
                   return Skip
                <|> do x <- identifier lis
                       reservedOp lis "="
                       e <- intexp
                       return (LetC x e)



------------------------------------
-- Función de parseo
------------------------------------
parseComm :: SourceName -> String -> Either ParseError Comm
parseComm = parse (totParser comm)
