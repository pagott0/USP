-- Verifica se um número é primo
isPrime :: Int -> Bool
isPrime n = isDivisible 2 n
  where
    isDivisible divisor dividend
      | divisor * divisor > dividend = True
      | dividend `mod` divisor == 0 = False
      | otherwise = isDivisible (divisor + 1) dividend

-- Recebe o número inicial e final, o maior intervalo calculado
checkDif :: Int -> Int -> Int -> Int
checkDif start end biggestInterval
  | start >= end = biggestInterval
  | isPrime start = checkDif (start + 1) end newInterval
  | otherwise = checkDif (start + 1) end biggestInterval
  where
    newInterval = if diff > biggestInterval && diff /= start then diff else biggestInterval
    diff = abs (start - findSecondPrime (start + 1) end)

-- Encontra o segundo número primo no intervalo
findSecondPrime :: Int -> Int -> Int
findSecondPrime start end
  | start >= end = if isPrime end then end else 0
  | isPrime start = start
  | otherwise = findSecondPrime (start + 1) end

main :: IO ()
main = do
  input1 <- getLine
  input2 <- getLine
  let a = read input1 :: Int
      b = read input2 :: Int
  print (checkDif a b 0)
