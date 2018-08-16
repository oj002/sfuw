import os

with open( input("Pleas enter a name for your generated library file:\n"), 'w') as fout:
    while 1:
        filePath = input("\nNow enter a file path of a library you want to add to extract into a file or enter x to stop:\n")
        if filePath == "x" or filePath == "X":
            break
        if os.path.exists(filePath):
            with open(filePath) as fin:
                for line in fin:
                    fout.write(line)
                fout.write("\n\n")
        else:
            print("File doesn't exist")
