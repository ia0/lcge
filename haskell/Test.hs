import Control.Monad
import Data.Char
import Data.Functor

main :: IO ()
main = interact (showBool . test . lines)
  where showBool True = "OK\n"
        showBool False = "ERROR\n"

test :: [String] -> Bool
test = and . map check . format
  where
    format [] = []
    format ("":end) = [] : format end
    format (s:end) = (readTerm s : ts) : tts
      where ts:tts = format end
    check [t] = reduce t == Nothing
    check (t:s:end) = reduce t == Just s && check (s:end)

data Term = Var Int
          | Abs Term
          | App Term Term
            deriving (Eq, Show, Read)

showTerm :: Term -> String
showTerm = flip go ""
  where
    go (Var n) end = show n ++ end
    go (Abs t) end = '\\' : go t end
    go (App t s) end = '(' : go t (')' : go s end)

readTerm :: String -> Term
readTerm cs = t
  where
    (t, "") = go cs
    go cs@(c:cs0)
      | c == '.' || c == '\\' = (Abs t, cs1)
      | c == '(' = (App t s, cs2)
      | isDigit c = (Var (read n), csn)
      where (t, cs1) = go cs0
            ')':cs1' = cs1
            (s, cs2) = go cs1'
            (n, csn) = span isDigit cs

iter :: (a -> Maybe a) -> a -> [a]
iter f x =
  case f x of
    Nothing -> [x]
    Just y -> x : iter f y

reduce :: Term -> Maybe Term
reduce (Var _) = Nothing
reduce (Abs t) = Abs <$> reduce t
reduce (App (Abs t) s) = Just (subst t 0 s)
reduce (App t s) = mplus (app (reduce t) (return s))
                         (app (return t) (reduce s))
  where app = liftM2 App

subst :: Term -> Int -> Term -> Term
subst t@(Var level) target term
  | level < target = t
  | level == target = shift term target 0
  | otherwise = Var (level - 1)
subst (Abs t) target term = Abs (subst t (target + 1) term)
subst (App t s) target term =
  App (subst t target term) (subst s target term)

shift :: Term -> Int -> Int -> Term
shift t@(Var level) shift_ scope
  | level < scope = t
  | otherwise = Var (level + shift_)
shift (Abs t) shift_ scope = Abs (shift t shift_ (scope + 1))
shift (App t s) shift_ scope =
  App (shift t shift_ scope) (shift s shift_ scope)
