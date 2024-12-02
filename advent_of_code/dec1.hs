{-# LANGUAGE TupleSections #-}
module Main where

import Data.List
import qualified Data.Map as M

main :: IO ()
main = do
  input <- readFile "dec1.txt"

  let [la, lb] = transpose
                 $ (read <$>) <$> words <$> lines input
      sla = sort la
      slb = sort lb

  -- part 1
  print . sum $ zipWith ( \ a b -> abs (a - b) ) sla slb

  -- was distracted by a movie, didn't notice part 2
  let lmb = M.fromList $ map (, 0) la
      lmb' = foldr ( \ b m -> M.insert (head b) (length b) m ) lmb $ group slb

  -- part 2
  print . sum $ map ( \ a -> a * lmb' M.! a) la
