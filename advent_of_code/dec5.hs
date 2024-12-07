module Main where

import Data.List
import Prelude hiding (lookup)
import Data.Map (Map)
import qualified Data.Map as M
import Data.Set (Set)
import qualified Data.Set as S

-- assume the input contains rule block first followed by empty line
-- followed by updates

-- 2 versions of splitOn, both splitting an input list into a list of
-- lists without the separator
splitOn1, splitOn2 :: Eq a => a -> [a] -> [[a]]
splitOn1 _ [] = []
splitOn1 a as = splitOn1' as []
  where splitOn1' [] rs = [rs]
        splitOn1' (b:bs) rs
          | a == b = rs : splitOn1' bs []
          | otherwise = splitOn1' bs (rs ++ [b])

splitOn2 _ []  = []
splitOn2 a as = let (r, rs) = splitOn2' as in r : splitOn2 a rs
  where splitOn2' [] = ([], [])
        splitOn2' (b:bs)
          | a == b = ([], bs) -- new split
          | otherwise =
              let (cs, ds) = splitOn2' bs in (b:cs, ds)

correctlyOrdered :: Map Int (Set Int) -> [Int] -> Bool
correctlyOrdered rules updates = correctlyOrdered' S.empty updates
  where updatesSet                    = S.fromList updates
        correctlyOrdered'    _     [] = True
        correctlyOrdered' seen (u:us) =
          let next = correctlyOrdered' (S.insert u seen) us
          in case M.lookup u rules of
               Nothing -> next
               Just before ->
                 not (any (\ b -> b `elem` updatesSet &&
                                  b `notElem` seen) before) && next

-- multimap fromList, using insertWith/union trick from
-- https://tech.fpcomplete.com/haskell/library/containers/
fromListMM :: (Ord a, Ord k) => [(k, a)] -> Map k (Set a)
fromListMM = foldr ( \ (k, v) m ->
                       M.insertWith S.union k
                       (S.singleton v) m ) M.empty

-- zip out a sublist by predicate, apply f on sublist, zip back into
-- original positions of input list
onSublist :: (a -> Bool) -> ([a] -> [a]) -> [a] -> [a]
onSublist p f as =
  let ps = map (\ a -> (p a, a)) as
      fsl = f $ snd <$> filter fst ps
      merge [] [] = []
      merge  ((True, _):xs) (y:ys) = y : merge xs ys
      merge ((False, x):xs)     ys = x : merge xs ys
      merge               _      _ = error "onSublist f changes length"
  in merge ps fsl

main :: IO ()
main = do
  input <- lines <$> readFile "dec5.txt"
  let
    -- read and convert text file, break rules and updates at empty
    -- line
    (rules, updates) = break null input
    rules' = (read <$>) . splitOn2 '|' <$> rules
    ruleSet = S.fromList (concat rules')
    ruleMMap = fromListMM $
               -- swap before/after for key/value Map lookup
               (\ [a, b] -> (b, a)) <$> rules'
    updates' = tail $ (read <$>) . splitOn2 ',' <$> updates
    -- rules are constant, use co function
    co = correctlyOrdered ruleMMap

  -- part 1
  print $ sum [ u !! (length u `div` 2) | u <- updates', co u ]

  let comp a b = case M.lookup b ruleMMap of
        Nothing -> GT -- leave in place
        Just a' -> if a `elem` a' then LT else GT

  -- part 2
  print $ sum [ u' !! (length u' `div` 2)
              | u <- updates'
                -- only correctly ordered updates
              , not $ co u
                -- use sortBy with rule map comparison
              , let u' = onSublist (`elem` ruleSet) (sortBy comp) u ]
