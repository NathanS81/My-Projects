# Tic Tac Toe Game

# Initialize the board
board = [" ", " ", " ", " ", " ", " ", " ", " ", " "]

# Function to display the board
def display_board():
    print(f"{board[0]}|{board[1]}|{board[2]}")
    print("-+-+-")
    print(f"{board[3]}|{board[4]}|{board[5]}")
    print("-+-+-")
    print(f"{board[6]}|{board[7]}|{board[8]}")

# Function to check if the game has been won
def check_win(player):
    if ((board[0] == player and board[1] == player and board[2] == player) or
        (board[3] == player and board[4] == player and board[5] == player) or
        (board[6] == player and board[7] == player and board[8] == player) or
        (board[0] == player and board[3] == player and board[6] == player) or
        (board[1] == player and board[4] == player and board[7] == player) or
        (board[2] == player and board[5] == player and board[8] == player) or
        (board[0] == player and board[4] == player and board[8] == player) or
        (board[2] == player and board[4] == player and board[6] == player)):
        return True
    else:
        return False

# Main game loop
def play_game():
    print("Welcome to Tic Tac Toe!")
    display_board()
    player = "X"
    winner = False
    while not winner and " " in board:
        print(f"{player}'s turn")
        position = int(input("Enter a position (1-9): ")) - 1
        if board[position] == " ":
            board[position] = player
            display_board()
            winner = check_win(player)
            if winner:
                print(f"{player} wins!")
            else:
                if player == "X":
                    player = "O"
                else:
                    player = "X"
        else:
            print("That position is already taken, please choose another.")
           
    if not winner:
        print("It's a tie!")

# Start the game
play_game()
