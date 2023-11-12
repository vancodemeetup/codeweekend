module Main where

strs1 = ["flower", "flow", "flight"]
strs2 = ["dog", "racecar", "car"]
strs3 = ["dog", "dog"]
strs4 = ["", "dog"]
strs5 = [""]
strs6 = []

firstCharsEqual :: [String] -> Maybe Char
firstCharsEqual [] = Nothing
firstCharsEqual strs =
  -- list of first character of each input string
  let firstChars = map head strs
  in if not (any null strs) &&
          (and $ zipWith (==) firstChars (tail firstChars)) then
         -- are all first characters equal
         Just (head firstChars)
       else
         -- one input string is empty or one character differs
         Nothing

longestCommonPrefix :: [String] -> String
longestCommonPrefix [] = ""
longestCommonPrefix strs =
  case firstCharsEqual strs of
    -- done once any character differs
    Nothing -> ""

    -- all first characters are equal, return the first character of
    -- the first string
    Just c -> c : longestCommonPrefix (map tail strs)

main :: IO ()
main = do
  print $ longestCommonPrefix strs1
  print $ longestCommonPrefix strs2
  print $ longestCommonPrefix strs3
  print $ longestCommonPrefix strs4
  print $ longestCommonPrefix strs5
  print $ longestCommonPrefix strs6
