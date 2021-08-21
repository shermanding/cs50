# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # TODO: Read teams into memory from file
    # create file variable which stores name of csv
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)

        # in this loop create dict keys and values by assigning team names and ratings
        for row in reader:
            name = row['team']
            rating = int(row['rating'])
            teams.append({'team': name, 'rating': rating})

    # declaring counts dictionary
    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts
    # for N simulations from i = 0 to 1000, simulate_tournament to get the winning team's name.
    for i in range(N):
        winning_team = simulate_tournament(teams)
        # if winning team's name already exists in count dictionary, add win count by 1 each iteration.
        if winning_team in counts:
            counts[winning_team] += 1
        # if winning team's name does not yet exist in count dictionary, include team's name in dictionary and set win count to 1
        else:
            counts[winning_team] = 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # while the length (number of items) in teams is still greater than 1, keep running simulation until 1 team is left
    while len(teams) > 1:
        teams = simulate_round(teams)

    # returns the 0 index row which is the number 1 and only team in the new list returned from simulate_round, fetching the 'team' column
    winner = teams[0]['team']
    return winner


if __name__ == "__main__":
    main()
