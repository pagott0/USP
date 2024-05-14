def checkSequence(numbers, index):
    if index == len(numbers) - 1:
        return 1
    elif numbers[index] < numbers[index + 1]:
        return 1 + checkSequence(numbers, index + 1)
    else:
        return 1

def getMaxLength(numbers, maxLength, currentIndex):
    if currentIndex == len(numbers):
        return maxLength
    newCount = checkSequence(numbers, currentIndex)
    newIndex = currentIndex + 1
    if newCount > maxLength:
        return getMaxLength(numbers, newCount, newIndex)
    else:
      return getMaxLength(numbers, maxLength, newIndex)

def longest_increasing_subsequence(numbers):
    if not numbers:
        return 0
    if len(numbers) == 1:
        return 1
    numbersSequenceMaxLength = getMaxLength(numbers, 0, 0)
    return numbersSequenceMaxLength

def main():
    input_str = input()
    numbers = list(map(int, input_str.split()))

    maxSequenceLength = longest_increasing_subsequence(numbers)

    print(maxSequenceLength)

if __name__ == "__main__":
    main()

