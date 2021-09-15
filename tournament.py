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
    # Read teams into memory from file
    try:
        with open(sys.argv[1], "r") as f:
            reads = csv.DictReader(f, fieldnames=("team", "rating"))
            for row in reads:
                if not row["rating"].isdigit():
                    continue
                row["rating"] = int(row["rating"])
                teams.append(row)
    except FileNotFoundError:
        sys.exit("File not found")

    counts = {}
    # Simulate N tournaments and keep track of win counts
    for tornament in range(N):
        winner = simulate_tournament(teams)
        if winner in counts:
            # Add to number of winners wins
            counts[winner] += 1 
        else:
            # If team win first time initialize key and value of dict
            counts.setdefault(winner, 1)

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


def simulate_tournament(teams: list) -> str:
    """Simulate a tournament. Return name of winning team."""
    # Copy teams in winner list
    winners = [x for x in teams]
    for i in range(len(teams) // 2):
        if len(winners) == 1:
            break
        winners = simulate_round(winners)

    return winners[0]["team"]


if __name__ == "__main__":
    main()
