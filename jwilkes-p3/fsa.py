from tkinter import Tk, Canvas, LAST, mainloop

import sys

if len(sys.argv) == 3:
    # Try to access both files
    try:
        with open(sys.argv[1]) as firstFile:
            firstContent = firstFile.read()
            print(firstContent)
    except EnvironmentError:
        print("Invalid first argument passed.")
        quit()
    try:
        with open(sys.argv[2]) as secondFile:
            secondContent = secondFile.read()
            print(secondContent)
    except EnvironmentError:
        print("Invalid second argument passed.")
        quit()

    # Try to parse through the fsa file
    try:
        fsa = firstContent.split(";")
        number_of_states = int(fsa[0])
        alphabet = fsa[1]
        state_transitions = fsa[2].split(",")
        start_state = int(fsa[3])
        accept_states = fsa[4].split(",")
    except ValueError:
        print("Invalid FSA file.")
        quit()

    # Global canvas variables
    circle_diameter = 50
    line_length = 100
    canvas_title = "Computer Programming Project 3 - FSA GUI"
    canvas_width = 350
    canvas_height = 50 + ((circle_diameter * number_of_states) +
                          (number_of_states - 1) * line_length)
    master = Tk()
    canvas = Canvas(master, width=canvas_width,
                    height=canvas_height, bg="white")

    # x and y coordinates to construct graph with
    x = canvas_width/2
    y = 25

    #nodes and links
    states = []
    links = []

    # Create first state
    states.append(canvas.create_oval(
        x - (circle_diameter/2), y, x + (circle_diameter/2), y + circle_diameter, fill="lightblue"))
    canvas.create_text(x, y + circle_diameter/2, text=0,
                       font="Arial 20")
    # Create every other state
    for index in range(number_of_states - 1):
        y = y + circle_diameter
        links.append(canvas.create_line(
            x, y, x, y + line_length, width=2, arrow=LAST))
        y = y + line_length
        states.append(canvas.create_oval(
            x - (circle_diameter/2), y, x + (circle_diameter/2), y + circle_diameter, fill="lightblue"))
        canvas.create_text(x, y + circle_diameter/2, text=index + 1,
                           font="Arial 20")

    for state in states:
        print(canvas.coords(state)[0], canvas.coords(
            state)[1], canvas.coords(state)[2], canvas.coords(state)[3], )

    canvas.pack()
    master.wm_title(canvas_title)
    mainloop()
else:
    print("Program requires two arguments: python fsa.py <fsa.txt> <legal/illegal.txt>")
    quit()
