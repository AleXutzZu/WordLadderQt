import csv
import random
from datetime import datetime, timedelta

def random_date(start, end):
    """Generate a random date between start and end (both datetime objects)."""
    delta = end - start
    random_days = random.randint(0, delta.days)
    return start + timedelta(days=random_days)

players = [f"player{i+1}" for i in range(10)]
start_date = datetime(2023, 1, 1)
end_date = datetime(2025, 6, 1)

for player in players:
    filename = f"{player}.csv"
    num_games = random.randint(5, 10)
    with open(filename, mode='w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        for _ in range(num_games):
            date = random_date(start_date, end_date).strftime("%Y-%m-%d")
            won = random.choice([0, 1])  # 0 = lost, 1 = won
            moves = random.randint(5, 50)
            hints = random.randint(0, 5)
            writer.writerow([date, won, moves, hints])

print("Dummy player CSV files generated.")
