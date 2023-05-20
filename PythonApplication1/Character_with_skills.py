class Character:
    def __init__(self, name, health, strength, agility):
        self.name = name
        self.health = health
        self.strength = strength
        self.agility = agility

    def attack(self, opponent):
        damage = self.strength
        if opponent.is_agile():
            damage //= 2
            print(f"{opponent.name} is too agile! {self.name}'s attack does half damage.")
        opponent.health -= damage
        print(f"{self.name} attacks {opponent.name} and deals {damage} damage.")

    def is_alive(self):
        return self.health > 0

    def is_agile(self):
        return self.agility >= 10

    def __str__(self):
        return f"{self.name} (Health: {self.health}, Strength: {self.strength}, Agility: {self.agility})"


# Create a new character
hero = Character("Hero", 100, 20, 5)

# Print the character's information
print(hero)

# Attack another character
enemy = Character("Enemy", 50, 10, 15)
hero.attack(enemy)

# Check if the enemy is still alive
print(enemy.is_alive())

