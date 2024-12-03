module Main where

import Data.List

diff :: [Int] -> [Int]
diff l = zipWith (-) l (tail l)

bounded, boundedNeg :: Int -> Bool
bounded x = 1 <= x && x <= 3
boundedNeg x = -3 <= x && x <= -1

allBounded :: [Int] -> Bool
allBounded l = all bounded l || all boundedNeg l

allBoundedDrop :: [Int] -> Bool
allBoundedDrop l =
  let lsDrop = l : zipWith (++) (init $ inits l) (tail $ tails l)
  in any allBounded $ diff <$> lsDrop

main :: IO ()
main = do
  input <- map (read <$>) . (words <$>) <$> lines <$> readFile "dec2.txt"

  -- part 1
  print . length . filter allBounded $ diff <$> input

  -- part 2
  print . length $ filter allBoundedDrop input
