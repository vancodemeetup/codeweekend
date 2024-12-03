module Main where

import Data.List

diff :: [Int] -> [Int]
diff l = zipWith (-) l (tail l)

bounded :: Int -> Int -> Int -> Bool
bounded lower upper x = lower <= x && x <= upper

allBounded :: [Int] -> Bool
allBounded l = all (bounded 1 3) l || all (bounded (-3) (-1)) l

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
