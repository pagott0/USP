
def transformPoints(throw):
  if(throw == 'X' or throw == '/'):
    return 10
  elif(throw == '-'):
    return 0
  else:
    return int(throw)

def calculateStrike(allFrames, index):
  strikePoints = 10
  if(index + 2 != len(allFrames) - 1 or index + 1 != len(allFrames)): #Casos em que o strike acontece no último frame. X12 (1 e 2 são números arbitrários) ou X1- (1 núm arbitrário)
    if(allFrames[index+2] == 'X'):
      strikePoints += calculateStrike(allFrames, index+2)
      return strikePoints
    elif (allFrames[index+2] == '/'):
      strikePoints += calculateSpare(allFrames, index+2)
      return strikePoints
    strikePoints += transformPoints(allFrames[index+2])
    if(allFrames[index+3] == '/'):
      strikePoints += calculateSpare(allFrames, index+3)
    else:
      strikePoints += transformPoints(allFrames[index+3])
  return strikePoints
  
def calculateSpare(allFrames, index):
  sparePoints = 10
  sparePoints -= transformPoints(allFrames[index-1])
  if(index + 1 != len(allFrames) - 1): #Caso em que o spare acontece no último frame.
    sparePoints += transformPoints(allFrames[index+1])
  return sparePoints
  

def calculaPlacar(allFrames):
  points = 0

  if(len(allFrames) != 21):
    raise Exception(f'Invalid number of frames, should be 21 but is: {len(allFrames)}')
  
  for i, throw in enumerate(allFrames):
    if(throw == 'X'):
      points += calculateStrike(allFrames, i)
    elif(throw == '/'):
      points += calculateSpare(allFrames, i)
    elif(throw == '-'):
      continue
    elif(throw.isdigit()):
      points += int(throw)
    else:
      raise Exception('Invalid character:', throw)
  return points

def main():
  print(calculaPlacar('8/90447290X-X-80359/7'))

if __name__ == "__main__":
  main()
