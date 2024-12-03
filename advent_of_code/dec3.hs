{-# LANGUAGE QuasiQuotes #-}
module Main where

-- cabal install --lib regex-with-pcre
import Text.RE.PCRE

main :: IO ()
main = do
  input <- concat . lines <$> readFile "dec3.txt"
  let multRE = [re|mul\(([0-9]+),([0-9]+)\)|]
      ms = input =~ multRE

  -- part 1
  print $ sum [ read a * read b :: Int | [_, a, b] <- ms ]

  let dontED = [ed|(don't\(\)).*?(do\(\))///|]
      ms2 = input *=~/ dontED =~ multRE

  -- part 2
  print $ sum [ read a * read b :: Int | [_, a, b] <- ms2 ]
