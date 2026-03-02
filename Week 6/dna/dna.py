import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Wrong number of command-line arguments")

    # TODO: Read database file into a variable
    database_list = []
    with open(sys.argv[1], "r") as database:
        reader_db = csv.DictReader(database)
        strs = reader_db.fieldnames[1:]
        for row in reader_db:
            database_list.append(row)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as sequence:
        seq = sequence.read()

    # TODO: Find longest match of each STR in DNA sequence
    row = []
    for i in range(len(strs)):
        row.append(longest_match(seq, strs[i]))

    # TODO: Check database for matching profiles
    # Here the strategy is to iterate within each dictionary to do the comparison of each STR and then iterate the whole list of the dictionaries to find the match
    for i in range(len(database_list)):
        match_number = 0
        for j in range(len(strs)):
            if int(database_list[i][strs[j]]) == row[j]:
                match_number += 1
        if match_number == len(strs):
            print(database_list[i]["name"])
            return
    print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in sequence, return longest run found
    return longest_run


main()
