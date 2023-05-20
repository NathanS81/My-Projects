import random
import tkinter as tk

def roll_dice():
    # Generate a random number between 1 and 6 (inclusive)
    number = random.randint(1, 6)

    # Update the label to display the result
    result_label.config(text=f"You rolled a {number}!")

# Create a new Tkinter window
window = tk.Tk()
window.title("Dice Roll")

# Create a label to display the result
result_label = tk.Label(window, text="Press the button to roll the dice!", font=("Arial", 20))
result_label.pack(pady=20)

# Create a button to roll the dice
roll_button = tk.Button(window, text="Roll", command=roll_dice, font=("Arial", 16))
roll_button.pack()

# Run the main loop
window.mainloop()