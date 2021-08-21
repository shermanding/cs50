import csv
import sys


def main():

    # ensure correct usage of program
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # opens database csv containing STR as database
    database = open(sys.argv[1])
    database_reader = csv.DictReader(database)

    # reads sequence txt to memory
    with open(sys.argv[2], "r") as txt:
        seq = txt.read()

    # counts dictionary
    count = {}

    # starting from 1 as fieldnames[0] = names
    # records counts of max occurences in txt file
    for i in range(1, len(database_reader.fieldnames)):
        STR = database_reader.fieldnames[i]
        # assign STR in count dict to max_match function of sequence file to be defined
        count[STR] = max_match(seq, STR)

    # checking for a match in database_reader one name at a time, if all STR in database file matches STR in seq file, prints out 'name' row in databse.
    for row in database_reader:
        # bool check where all counts of STR in seq matches integer value of STR in database for each STR inside counts dict
        if all(count[STR] == int(row[STR]) for STR in count):
            # print "name" in database if bool check passes
            print(row['name'])
            return

    print("No match")
    database.close()


def max_match(seq, STR):
    # nested loop to find STR in seq file
    maximum = 0

    for j in range(len(seq)):
        counter = 0

        # if STR match is found
        while True:

            start = j + len(STR) * counter
            end = start + len(STR)

            # nested loop that increments counter everytime matching STR is found. Counter multiplier to length of STR to start where it last matched
            # e.g TATC starts from 76th character in 1.txt and ends at 95th character. Next sequence STR comparison starts from length 4 * 5 = 20 characters later
            if seq[start:end] == STR:
                counter += 1
            else:
                break

        # update maximum with the larger number between maximum and counter
        maximum = max(maximum, counter)

    return maximum



main()