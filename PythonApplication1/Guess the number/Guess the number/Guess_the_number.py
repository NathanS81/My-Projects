
import random

print("Welcome to Guess the Number!")
print("I'm thinking of a number between 1 and 100. Can you guess it?")

# generate random number between 1 and 100
number = random.randint(1, 100)

# initialize variables
guess = 0
tries = 0

# loop until player guesses correctly
while guess != number:
    # ask player for guess
    guess = int(input("Enter your guess: "))
    tries += 1

    # give hint
    if guess < number:
        print("Too low!")
    elif guess > number:
        print("Too high!")
    else:
        print("You got it!")

print("It took you", tries, "tries to guess the number.")