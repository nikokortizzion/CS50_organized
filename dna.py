""" Program check if sequence in data base
and print name of person whom it belongs."""
import sys
import csv
import re


def count_STR(DNA: str, STR: str) -> int:
    """ Count consequtive entry STR in DNK
    and returns max count"""
    counter, maxcount = 0, 0  # counters
    start = DNA.find(STR)  # start point of DNA for counting
    tmp = DNA[start:-1]  # slice DNA from start point to end
    while tmp:
        # Check if DNA starts with STR
        if tmp.startswith(STR):
            start = len(STR)
            tmp = tmp[start: -1]
            counter += 1
            continue
        else:
            # Stop counting and check if counter has maximum value
            if maxcount < counter:
                maxcount = counter
                counter = 0
            else:
                counter = 0
            # Search new start point
            start = tmp.find(STR)
            tmp = tmp[start: -1]
    # Return maximum value of counter
    return maxcount


def main():
    # Check if program start in correct way
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py base.csv sequence.txt")
    else:
        if not re.findall(r'[^A-Za-z0-9_\-\/]csv$', sys.argv[1]) or not re.findall(
                r'[^A-Za-z0-9_\-\/]txt$', sys.argv[2]):
            sys.exit("Usage: python dna.py base.csv sequence.txt")
    database = read_csv(sys.argv[1])
    DNA = read_sequence(sys.argv[2])
    # Check if DNA has STR from data base
    sample = {}
    for k in database[0].keys():
        if k == 'name':
            continue
        sample[k] = count_STR(DNA, k)

    # Search sample in data_base
    for item in database:
        name = item['name'] if len(sample) == sum(
            [v == int(item[k]) for k, v in sample.items()]) else ""
        if name:
            break
    # Print name or No match
    print(f"{name if name else 'No match'}")


def read_csv(base):
    # Read csv file database
    database = []
    try:
        with open(base) as f:
            reads = csv.DictReader(f)
            for item in reads:
                # Create data base in memory
                database.append(item)
    except FileNotFoundError:
        sys.exit(f"File not found: {base}")
    return database


def read_sequence(sequence):
    # Read txt file sequence
    try:
        with open(sequence) as f:
            for row in f:
                # Create string DNA in memory from sequence
                DNA = row
    except FileNotFoundError:
        sys.exit(f"File not found: {sequence}")
    return DNA


if __name__ == '__main__':
    main()
