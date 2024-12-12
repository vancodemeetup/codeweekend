module Main where

import Data.List
import qualified Data.Map as M

-- inexact Double log
rewrite :: Integer -> [Integer]
rewrite 0 = [1]
rewrite i =
  let nDigits = floor (logBase 10 $ fromIntegral i :: Double) + 1
      (l, r) = divMod i (10^(nDigits `div` 2))
  in if even (nDigits :: Integer) then [l, r] else [i * 2024]

blink :: [Integer] -> [Integer]
blink = concatMap rewrite'

blinkN :: Int -> [Integer] -> [Integer]
blinkN n = foldr1 (.) $ replicate n blink

-- exact show/count
rewrite' :: Integer -> [Integer]
rewrite' 0 = [1]
rewrite' i =
  let nDigits = length (show i)
      (l, r) = divMod i (10^(nDigits `div` 2))
  in if even nDigits then [l, r] else [i * 2024]

-- memoization for 75 blinks
lengthBlink :: Int -> [Integer] -> Integer
lengthBlink level is =
  fst $ lengthBlink' level M.empty is
  where lengthBlink'     0      memo      js = (genericLength js, memo)
        lengthBlink'     _      memo      [] = (0, memo)
        lengthBlink' level'  memo (j:js) =
          case M.lookup (level', j) memo of
            Nothing ->
              let l = rewrite' j
                  (len, memo') = lengthBlink' (level' - 1) memo l
                  (len', memo'') = lengthBlink' level' (M.insert (level', j) len memo') js
              in (len + len', memo'')
            Just len ->
              let (len', memo') = lengthBlink' level' (M.insert (level', j) len memo) js
              in (len + len', memo')

main :: IO ()
main = do
  input <- (read <$>) .  words <$> readFile "dec11.txt"

  -- part 1
  print . length $ blinkN 25 input

  -- part 2
  print $ lengthBlink 75 input
