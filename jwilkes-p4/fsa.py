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

    # Make Lisp program from Python variables: Create numbersToWords dictionary and open file
    numbersToWords = {0: 'Zero', 1: 'One', 2: 'Two', 3: 'Three', 4: 'Four', 5: 'Five',
                      6: 'Six', 7: 'Seven', 8: 'Eight', 9: 'Nine', 10: 'Ten',
                      11: 'Eleven', 12: 'Twelve', 13: 'Thirteen', 14: 'Fourteen',
                      15: 'Fifteen', 16: 'Sixteen', 17: 'Seventeen', 18: 'Eighteen',
                      19: 'Nineteen', 20: 'Twenty'}
    part_two = open("part_two.lsp", "w")
    program = []

    # Begin demo function
    program.append("(DEFUN demo()\n" +
                   "    (setq *startState* " + str(start_state) + ")\n" +
                   "    (setq fp (open \"theString.txt\" :direction :input))\n" +
                   "    (setq *path* (read fp \"done\"))\n" +
                   "    (cond\n")
    for i in range(number_of_states):
        program.append(
            "        ((equal *startState* " + str(i) + ") (state" + numbersToWords.get(i) + " *path*))\n")
    program.append(
        "    )\n" +
        ")\n\n")

    # Begin state functions
    for i in range(number_of_states):
        pathOptions = filter(lambda x: x[0] == i, state_transitions)
        program.append(
            "(DEFUN state" + numbersToWords.get(i) + "(route)\n" +
            "    (cond ((null route) (acceptState " + str(i) + "))\n")
        for pathOption in pathOptions:
            program.append(
                "        ((string-equal (car route) \"" +
                str(pathOption[2]).capitalize() + "\")(state" +
                numbersToWords.get(pathOption[1]) + " (cdr route)))\n"
            )
        program.append(
            "        (t (princ \"Illegal route.\"))\n" +
            "    )\n" +
            ")\n\n")

    # Begin accept states function
    program.append(
        "(DEFUN acceptState (n)\n    (cond\n")
    for i in accept_states:
        program.append(
            "        ((equal n " + str(i) + ")(princ \"Route legal.\"))\n")
    program.append(
        "        (t (princ \"Route not legal.\"))\n" +
        "    )\n" +
        ")\n\n")

    for piece in program:
        part_two.write(piece)
    part_two.close()
    print("Now try the Lisp program!\nOpen up \"xlwin32.exe\", and type \"(load \"part_two.lsp\")\", then \"(demo)\".  Just make sure \"theString.txt\" exists!")
else:
    print("Program requires two arguments: python fsa.py <fsa.txt> <legal/illegal.txt>")
    quit()
