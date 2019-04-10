import math
import random
import sys

if len(sys.argv) == 3:
    # Try to access both files
    try:
        with open(sys.argv[1]) as firstFile:
            firstContent = firstFile.read()
    except EnvironmentError:
        print("Invalid first argument passed.")
        quit()
    try:
        with open(sys.argv[2]) as secondFile:
            secondContent = secondFile.read()
    except EnvironmentError:
        print("Invalid second argument passed.")
        quit()
    # Try to parse through the fsa file
    try:
        fsa = firstContent.split(";")
        number_of_states = int(fsa[0])
        alphabet = fsa[1]
        state_transitions = fsa[2].split(",")
        # To strip and split the state transitions: iterate through state_transitions list
        for i, trans in enumerate(state_transitions):
            # Left and right strip the parantheses from the state_transitions list
            trans = trans.lstrip("(")
            trans = trans.rstrip(")")
            # Split each transition on colon
            trans = trans.split(":")
            # Iterate through the resultant array
            for index in range(3):
                # Make the first two values integers, keeping the third as a string
                if index != 2:
                    trans[index] = int(trans[index])
            # Assign trans to its position in the state_transitions array to update value
            state_transitions[i] = trans
        start_state = int(fsa[3])
        accept_states = fsa[4].split(",")
        # Change accept_states array to integers instead of strings
        for i in range(len(accept_states)):
            accept_states[i] = int(accept_states[i])
        pathString = list(map(str, secondContent))
    except ValueError:
        print("Invalid FSA file.")
        quit()
    states = []
    # Now parse through the pathString to determine if the path is legal with current_node_in_path starting at start_state
    current_node_in_path = start_state
    legal_path = True
    error_message = ""
    for path in pathString:
        # Check for illegal paths in the pathString against the alphabet
        if path not in alphabet:
            error_message = "Path " + path + " is not a valid transition state."
            legal_path = False
            break
        # If current character in pathString is a newline, space, or tab, just continue
        if path == "\n" or path == " " or path == "\t":
            continue
        # If current character in pathString is found (not -1) in the valid path variables (alphabet)
        if(alphabet.find(path) != -1):
            # Return an array of the possible path options from state_transitions
            pathOptions = filter(
                lambda x: x[0] == current_node_in_path, state_transitions)
            # In each state transition
            for pathOption in pathOptions:
                # If current character in pathString finds an acceptable pathj
                if path == pathOption[2]:
                    # Then take that path, and make sure legal_path is True and break from inner for loop
                    current_node_in_path = pathOption[1]
                    legal_path = True
                    break
                else:
                    # Else, make sure legal_path remains false
                    legal_path = False
        # If legal_path was found false at the end of each 'path' loop, break loop
        if legal_path == False:
            error_message = "Illegal path option: State: " + \
                str(current_node_in_path) + ", Path: " + path
            break
    # Check if the final state of the program is in accept_states, else update error message
    if legal_path and current_node_in_path not in accept_states:
        legal_path = False
        error_message = "Illegal final state: " + \
            str(current_node_in_path) + ", must be: " + accept_states
    # Print result of path and error if illegal
    if legal_path:
        print("Path is legal!  Ended on node: " + str(current_node_in_path))
    else:
        print("Path is not legal :(.  Here's why: ", error_message)
else:
    print("Program requires two arguments: python fsa.py <fsa.txt> <legal/illegal.txt>")
    quit()