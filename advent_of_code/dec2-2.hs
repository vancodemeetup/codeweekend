module Main where

check :: Bool -> [Int] -> Bool
check _ [] = True
check _ [_] = True
check dropped (x:xs@(x':_)) =
  case compare x x' of
    EQ -> not dropped && check True xs
    LT -> checkDiffs dropped ( 1,  3) x xs || (not dropped && check True xs)
    GT -> checkDiffs dropped (-3, -1) x xs || (not dropped && check True xs)

checkDiffs :: Bool -> (Int, Int) -> Int -> [Int] -> Bool
checkDiffs       _                           _ _      [] = True
checkDiffs dropped bs@(lowerBound, upperBound) x (x':xs) =
  let diff = x' - x
      inBounds = lowerBound <= diff && diff <= upperBound
  in (inBounds && checkDiffs dropped bs x' xs)
     || (not inBounds && not dropped && checkDiffs True bs x xs)

main :: IO ()
main = do
  input <- map (read <$>) . (words <$>) <$> lines <$> readFile "dec2.txt"

  -- part 1
  print . length $ filter (check True) input

  -- part 2, two-pass without generating all input lists
  print . length $ filter (check False) input
