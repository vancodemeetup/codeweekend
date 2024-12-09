{-# LANGUAGE TupleSections #-}
module Main where

import Data.List
import qualified Data.Map as M
import Data.Char

pairs :: [a] -> [(a, a)]
pairs [] = []
pairs (a:as) = map (a,) as ++ pairs as

main :: IO ()
main = do
  input <- lines <$> readFile "dec8.txt"

  let h = length input
      w = length (head input)

      antennas = foldr ( \ (k, v) m -> M.insertWith (++) k [v] m ) M.empty
                 [ (c, (x, y))
                 | (y, line) <- zip [1 ..] input
                 , (x, c) <- zip [1 ..] line
                 , isAlphaNum c ]

      inBounds (x, y) = 1 <= x && x <= w &&
                        1 <= y && y <= h

      antidotes' (x1, y1) (x2, y2) justOne =
        takeWhile inBounds
        $ (if justOne then take 1 else id)
        [ (x2 + a*dx, y2 + a*dy)
        | let dx = x2 - x1; dy = y2 - y1
        , a <- [if justOne then 1 else 0 .. ] ]

      antidotes as justOne =
        concat . concat
        $ [ [ antidotes' p1 p2 justOne
            , antidotes' p2 p1 justOne ]
          | (p1, p2) <- pairs as ] :: [(Int,Int)]

      result justOne =
        length . nub $ concat
        [ antidotes coords justOne
        | (_, coords) <- M.assocs antennas ]

  -- part 1, there are actually up to 4 points that have the
  -- same/double distance to 2 antennas, yet only the outer ones count
  print (result True)

  -- part 2, detailed rules that also include the antennas themselves
  print (result False)

