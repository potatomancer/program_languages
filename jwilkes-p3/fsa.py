from tkinter import Tk, Canvas, LAST, mainloop
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
        pathString = list(map(str, secondContent))
    except ValueError:
        print("Invalid FSA file.")
        quit()
    # Global canvas variables
    circle_diameter = 50
    line_length = 100
    line_width = 2
    line_active_width = 4
    line_arrow_shape = (9, 10, 9)
    canvas_title = "COP4020 Project 3 - FSA GUI"
    canvas_width = 500
    # Height is dependent based on number of states
    canvas_height = 50 + ((circle_diameter * number_of_states) +
                          (number_of_states - 1) * line_length)
    master = Tk()
    canvas = Canvas(master, width=canvas_width,
                    height=canvas_height, bg="white")
    # x and y coordinates to construct graph with
    x = canvas_width/2
    y = 25
    # nodes
    states = []
    # Create every state
    for index in range(number_of_states):
        if index == 0:
            # Create first state
            states.append(canvas.create_oval(
                x-(circle_diameter/2),
                y,
                x+(circle_diameter/2),
                y+circle_diameter, fill="lightblue"))
            canvas.create_text(x, y+circle_diameter/2,
                               text=index+start_state, font="Arial 20")
        else:
            # Fix height of y to the bottom of the circle
            y = y + circle_diameter + line_length
            # Create new circle and append it to the states list
            states.append(canvas.create_oval(
                x-(circle_diameter/2),
                y,
                x+(circle_diameter/2),
                y+circle_diameter, fill="lightblue"))
            # Create state text and place it in the center of the circle, Arial 20 because I like to style things don't @ me
            canvas.create_text(x, y + circle_diameter/2,
                               text=index + start_state, font="Arial 20")
    # Create variable for measuring how many multiple state transitions (MST) happen and a variable for the padding
    mst_number = 0
    mst_padding = 25
    # Create every state transition per state
    for index in range(number_of_states):
        transitions = filter(lambda x: x[0] == index, state_transitions)
        for z in transitions:
            # Reset x, y position to the bottom of the current state circle
            coords = canvas.coords(states[index])
            x = coords[2] - (circle_diameter/2)
            y = coords[3]
            # Generate random activefill color for line
            activefill = "#{:06x}".format(random.randint(0, 0xFFFFFF))
            # From current state to same state
            if z[1] == index:
                # Place x, y position at center of current circle
                y = y - circle_diameter/2
                # Create line that curves out from circle and points back to circle
                canvas.create_line(
                    x+(circle_diameter/2)*math.cos(math.pi/4),
                    y+(circle_diameter/2)*math.sin(math.pi/4),
                    x+circle_diameter-(circle_diameter/2) *
                    math.cos(math.pi/2),
                    y+(circle_diameter/2)*math.sin(math.pi/4),
                    x+circle_diameter+(circle_diameter/2) *
                    math.cos(math.pi/2),
                    y-(circle_diameter/2)*math.sin(math.pi/4),
                    x+(circle_diameter/2)*math.cos(math.pi/4),
                    y-(circle_diameter/2)*math.sin(math.pi/4),
                    width=line_width, activewidth=line_active_width, arrow=LAST,
                    arrowshape=line_arrow_shape, smooth=True, activefill=activefill)
                # Give line its label
                canvas.create_text(x + 15 + circle_diameter, y, text=z[2],
                                   font="Arial 20")
            # From current state to next state:
            elif z[1] == index + 1:
                # Create new line, append it to the links list
                line = canvas.create_line(
                    x, y, x, y + line_length,
                    width=line_width, activewidth=line_active_width,
                    arrow=LAST, arrowshape=line_arrow_shape, activefill=activefill)
                text = canvas.create_text(x + 10, y+line_length/2, text=z[2],
                                          font="Arial 20")
            # From current state jumping to state more than one away
            elif z[1] - z[0] > 1 or z[1] - z[0] < -1:
                # Increment multiple state transition number
                mst_number = mst_number + 1
                # Set y to center of state circle
                y = y-(circle_diameter/2)
                # Set new x, y to the left side of the state circle
                x = x-(circle_diameter/2)*math.sin(math.pi/2)
                y = y-(circle_diameter/2)*math.cos(math.pi/2)
                # Get the difference of states between current and target state
                difference_states = z[1] - z[0]
                canvas.create_line(
                    x,  # Start at left side of circle
                    y,
                    # Go out by padding * mst number
                    x-(mst_padding*mst_number),
                    y,
                    x-(mst_padding*mst_number),  # Go up to target circle
                    y+((circle_diameter+line_length)*difference_states),
                    x,  # Touch target circle
                    y+((circle_diameter+line_length)*difference_states),
                    width=line_width, activewidth=line_active_width, activefill=activefill,
                    arrow=LAST, arrowshape=line_arrow_shape)
                # Create label for arrow
                canvas.create_text(
                    x-(mst_padding*mst_number)+10,
                    y+(((circle_diameter+line_length)*difference_states)/2),
                    text=z[2],
                    font="Arial 20")
    # Now parse through the pathString to determine if the path is legal with currentNodeInPath starting at 0
    currentNodeInPath = 0
    legalPath = True
    for path in pathString:
        # If current character in pathString is a newline, space, or tab, just continue
        if path == "\n" or path == " " or path == "\t":
            continue
        # If current character in pathString is found (not -1) in the valid path variables (alphabet)
        if(alphabet.find(path) != -1):
            # Return an array of the possible path options from state_transitions
            pathOptions = filter(
                lambda x: x[0] == currentNodeInPath, state_transitions)
            # In each state transition
            for pathOption in pathOptions:
                # If current character in pathString finds an acceptable pathj
                if path == pathOption[2]:
                    # Then take that path, and make sure legalPath is True and break from inner for loop
                    currentNodeInPath = pathOption[1]
                    legalPath = True
                    break
                else:
                    # Else, make sure legalPath remains false
                    legalPath = False
        # If legalPath was found false at the end of each 'path' loop, break loop
        if legalPath == False:
            break
    # Print result of path
    if legalPath:
        print("Path is legal!")
    else:
        print("Path is not legal :(")
    # Create clarifying text to indicate that arrows can be scrolled over
    canvas.create_text(canvas_width/2, canvas_height - 10, text="*If lines overlap, please scroll over the line.",
                       font="Arial 12")
    # Pack it up, title it up, loop it up!
    canvas.pack()
    master.wm_title(canvas_title)
    mainloop()
else:
    print("Program requires two arguments: python fsa.py <fsa.txt> <legal/illegal.txt>")
    quit()
