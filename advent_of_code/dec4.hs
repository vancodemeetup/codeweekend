module Main where

import Data.Array

type Board = Array Int (Array Int Char)

check :: Board -> Int ->  Int -> String
      -> Int -> Int -> Int -> Int -> Bool
check board w h str x dx y dy =
  and [ check' c nx ny | (c, nx, ny) <- zip3 str [x, x + dx ..] [y, y + dy ..] ]
  where check' c nx ny
          | 1 <= nx && nx <= w &&
            1 <= ny && ny <= h = c == board ! nx ! ny
          | otherwise = False

main :: IO ()
main = do
  input <- lines <$> readFile "dec4.txt"

  let board = listArray (1, length input)
              [ listArray (1, length i) i | i <- input ]
      (1, h) = bounds board
      (1, w) = bounds (board ! 1)

      check' = check board w h

  -- part 1
  print $ length
    [ () | y <- [1 .. h], x <- [1 .. w]
         , dx <- [-1, 0, 1], dy <- [-1, 0, 1]
         , check' "XMAS" x dx y dy ]

  -- part 2
  print $ length
    [ () | y <- [1 .. h - 2], x <- [1 .. w - 2]
         , s1 <- [ "MAS", "SAM" ], s2 <- [ "MAS", "SAM" ]
         , check' s1 x 1 y 1 && check' s2 (x + 2) (-1) y 1 ]
