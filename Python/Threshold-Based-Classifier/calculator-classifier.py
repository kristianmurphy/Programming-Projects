## Calculator:

import math ## import math library to help with certain calculator operations

def input_num(prompt):  ## Input_num function is a modified input function to take only numbers
  inputvar = input(prompt)
  if inputvar is 'x':
    return False. ## if x, close
  try:
    return float(inputvar)  ## if number, will return input as float
  except ValueError:
    return input_num(prompt). ## if not number, calls recursively

def calculation(): ## First section:
  number1 = input_num("Enter the first number or x to exit: ") ## Take first number input ( must be number, using input num )
  if number1 is False: return ## close if x (x returned false)
  print("Operations: summation, subtraction, multiplication, division, mod, power, exp, natural log, and abs")
  op = operation("Enter the operation or x to exit: ", number1) ## call operation to take correct input and carry out operation
  if op is False: return ## close if x
  print("\nNext Operation") ## continue
  calculation() ## call recursively until returned with x

def operation(prompt, num1):
  inputop = input(prompt) ## input op will start with user input

  if inputop is 'x': ## if x, returns back to close program
    return False

  elif inputop == "summation": ## if summation, input second number and add
    number2 = input_num("Enter the second number or x to exit: ")
    if number2 is False: return False
    print("Output of the operation: " + str(num1 + number2))

  elif inputop == "subtraction": ## if subtraction, input second number and subtract
    number2 = input_num("Enter the second number or x to exit: ")
    if number2 is False: return False
    print("Output of the operation: " + str(num1 - number2))

  elif inputop == "multiplication": ## if multiplication, take second number and multiply
    number2 = input_num("Enter the second number or x to exit: ")
    if number2 is False: return False
    print("Output of the operation: " + str(num1 * number2))

  elif inputop == "division": ## if division, take second number and divide
    number2 = input_num("Enter the second number or x to exit: ")
    if number2 is False: return False
    print("Output of the operation: " + str(num1 / number2))

  elif inputop == "mod": ## if modulo, take second number and find modulo
    number2 = input_num("Enter the second number or x to exit: ")
    if number2 is False: return False
    print("Output of the operation: " + str(num1 % number2))

  elif inputop == "power": ##if power, take second number to the first numbers exponent
    number2 = input_num("Enter the second number or x to exit: ")
    if number2 is False: return False
    print("Output of the operation: " + str(num1 ** number2))

  elif inputop == "exp": ## if exponential, find power of e
    print("Output of the operation: " + str(math.exp(num1)))

  elif inputop == "natural log": ## if natural log, find the base ten log
    print("Output of the operation: " + str(math.log(num1)))

  elif inputop == "abs": ## if abs, find absolute value
    print("Output of the operation: " + str(abs(num1)))

  else:
    return operation(prompt, num1) ## if input not listed, restart since invalid

print('_____________ Calculator _____________\n') ## print beginning of calculator interface
calculation() ## start calculation by calling



## Threshold-based classifier:

# %matplotlib inline ## set up plotting
import matplotlib.pyplot as plt
import numpy as np


c1 = np.array([(1, 1), (3, 2), (2, 3)]) ## Classication 1 with attributes
c2 = np.array([(1, 2), (2, 2), (2, 1)]) ## Classication 2 with attributes

plt.scatter(c1[:,0],c1[:,1], color="red", marker="v", label = "C1") ## plot with diff shapes and colors
plt.scatter(c2[:,0],c2[:,1], color="green", marker="^", label = "C2")
plt.xlabel("Attribute x") ## labels
plt.ylabel("Attribute y")
plt.legend() ## legend


def check_accuracy(classification, classname, x, y):
  num_correct = 0 ## start num correct at 0
  for c in classification:
    if classname == "c1":
      if c[0] > x and c[1] > y:
        num_correct += 1  ## increment num correct if conditions met
    if classname == "c2":
      if c[0] <= x or c[1] <= y:
        num_correct += 1
  return num_correct ## return when done processing all points

for x in range(3):
  thx = input_num("Enter threshold value for thx: ")
  thy = input_num("Enter threshold value for thy: ")
  accuracy = (check_accuracy(c1, "c1", thx, thy)) + (check_accuracy(c2, "c2", thx, thy))
  accuracy = accuracy/6 ## calculate accuracy
  print("Accuracy: " + str(accuracy*100) + "%")
