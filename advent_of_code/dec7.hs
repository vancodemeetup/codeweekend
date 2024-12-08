module Main where

readLine :: [String] -> [Integer]
readLine [] = error "empty line"
readLine (result:as) = read (init result) : map read as

search :: [Integer -> Integer -> Integer] -> [Integer] -> Bool
search _   [] = error "empty line"
search _   [_] = error "no operands"
search ops (result:a:as) = search' a as
  where search' acc [] = acc == result
        search' acc (b:bs)
          | acc > result = False
          | otherwise = or [ search' (acc `op` b) bs | op <- ops ]

main :: IO ()
main = do
  input <- (words <$>) . lines <$> readFile "dec7.txt"
  let input' = map readLine input

  -- part 1
  print . sum . map (head . snd) . filter fst
    $ zip (map (search [ (+), (*) ]) input') input'

  let append a b = read (show a ++ show b)

  -- part 2, note concatenation is unintuitive, not using higher
  -- precedence but on left-to-right on accumulator and next operand
  print . sum . map (head . snd) . filter fst
    $ zip (map (search [ (+), (*), append ]) input') input'
