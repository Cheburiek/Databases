

def showMainMenu():
    print("\n\n KV-02 Maistrenko Olga. Lab Work 3")
    print("        Maistrenko Olga")
    print("        Lab Work 3")
    print("\n\n")
    print(" >>> PROGRAM MENU <<< ")
    print(" 1. Insert data in table")
    print(" 2. Remove data in table")
    print(" 3. Edit data in table  ")
    print(" What do you want to do? ")


def getSplitInput():
    inp = input().split(', ')
    return inp


def getInput(string):
    if string is None:
        inp = input(" > ")
    else:
        inp = input(string)
    return inp
