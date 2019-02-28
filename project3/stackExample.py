#!/usr/bin/env
import sys
import tkinter as tk


class Stack:
    def __init__(self):
        self.items = []

    def isEmpty(self):
        return self.items == []

    def push(self, item):
        self.items.append(item)

    def pop(self):
        return self.items.pop()

    def peek(self):
        return self.items[len(self.items)-1]

    def size(self):
        return len(self.items)


""" out = open('out.txt', 'w')

if len(sys.argv) > 1:
    file = open(sys.argv[1])
    if file:
        for line in file:
            print(line)

stack = Stack()
stack.push(1)
stack.push(2)
print(str(stack.pop()) + ' bitches, ah-ah-ah')
print(str(stack.pop()) + ' bitch, ah-ah-ah') """
