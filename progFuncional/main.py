
# Online Python - IDE, Editor, Compiler, Interpreter

def is_prime(n):
    def is_divisible(divisor, dividend):
        if divisor * divisor > dividend:
            return True
        elif dividend % divisor == 0:
            return False
        else:
            return is_divisible(divisor + 1, dividend)

    if n <= 1:
        return False
    return is_divisible(2, n)

#recebe o numero inicial e final, o maior intervalo calculado
def checkDif(start, end, biggestInterval):
    if(start >= end):
        return biggestInterval
    isPrime = is_prime(start)
    if(isPrime):
        diff = abs(start - findSecondPrime(start + 1, end))
        if(diff > biggestInterval and diff != start):
            return checkDif(start + 1, end, diff)
        return checkDif(start + 1, end, biggestInterval)
    return checkDif(start + 1, end, biggestInterval)

def findSecondPrime(start, end):
    if(start >= end):
        if(is_prime(end)):
            return end
        return 0
    if(is_prime(start)):
        return start
    return (findSecondPrime(start + 1, end))

a = int(input(''))
b = int(input(''))

print(checkDif(a, b, 0))
