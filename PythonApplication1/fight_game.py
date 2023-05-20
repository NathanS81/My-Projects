import random

class Fighter:
    def __init__(self, name, health, strength, defense):
        self.name = name
        self.health = health
        self.strength = strength
        self.defense = defense

    def attack(self, opponent):
        damage = self.strength - opponent.defense
        damage = max(damage, 0)
        opponent.health -= damage
        print(f"{self.name} attacks {opponent.name} and deals {damage} damage.")

    def is_alive(self):
        return self.health > 0

    def __str__(self):
        return f"{self.name} (Health: {self.health}, Strength: {self.strength}, Defense: {self.defense})"


class FightingGame:
    def __init__(self, fighter1, fighter2):
        self.fighter1 = fighter1
        self.fighter2 = fighter2

    def fight(self):
        print(f"Fighter 1: {self.fighter1}")
        print(f"Fighter 2: {self.fighter2}")
        print("Let the battle begin!")
        round_num = 1

        while self.fighter1.is_alive() and self.fighter2.is_alive():
            print(f"Round {round_num}")
            # Fighter 1 attacks Fighter 2
            self.fighter1.attack(self.fighter2)
            if not self.fighter2.is_alive():
                break
            # Fighter 2 attacks Fighter 1
            self.fighter2.attack(self.fighter1)
            if not self.fighter1.is_alive():
                break
            round_num += 1

        if self.fighter1.is_alive():
            print(f"{self.fighter1.name} wins!")
        else:
            print(f"{self.fighter2.name} wins!")

# Create two fighters
fighter1 = Fighter("John", 100, 20, 10)
fighter2 = Fighter("Jane", 100, 15, 15)

# Create a new fighting game with the two fighters
game = FightingGame(fighter1, fighter2)

# Start the game
game.fight()
