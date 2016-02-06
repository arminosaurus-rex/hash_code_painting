import sys

def valid_coordinates(r1, c1):
    return (0 <= r1) && (r1 < rows) && (0 <= c1) && (c1 < columns)

def valid_square(r, c, s):
    corners = [(r + a*s, c + b*s) for a in [-1,1] for b in [-1,1]]
    for cord in corners:
        if not valid_coordinates(cord[0], cord[1]):
            return False

    return True

# Read the path of the images from the command line
path_image = sys.argv[1]
path_solution = sys.argv[2]

# Convert the image into a boolean array
image_file = open(path_image, 'r')
rows, columns = map(int, image_file.readline().split())

image = [[0 for c in range(columns)] for r in range(rows)]

num_pixels = 0

for r in range(rows):
    current_line = image_file.readline.split()
    for c in range(columns):
        if current_line[i] == '#':
            image[r][c] = 1
            num_pixels = num_pixels + 1

# Check with the solution
solution_file = open(path_solution, 'r')
num_commands = int(solution_file.readline.split())


valid_solution = True
painted_image = [[0 for c in range(columns)] for r in range(rows)]

for i in range(num_commands):
    command = solution_file.readline.split()
    if command[0] == 'PAINT_SQUARE':
        if not len(command) == 4:
            print(command + " in line " + str(i+2) + " is not a valid command!")
            valid_solution = False
        else:
            R, C, S = map(int, command[1:4])
            if not valid_coordinates(R, C, S):
                print(command + " in line " + str(i+2) + " is not a valid command!")
                valid_solution = False
            else:
                for r in range(R-S, R+S+1):
                    for c in range(C-S, C+S+1):
                        painted_image[r][c] = 1

    elif command[0] == 'PAINT_LINE':
        if not len(command) == 5:
            print(command + " in line " + str(i+2) + " is not a valid command!")
            valid_solution = False
        else:
            R1, C1, R2, C2 = map(int, command[1:5])
            if not valid_coordinates(R1, C1) or not valid_coordinates(R2, C2):
                print(command + " in line " + str(i+2) + " is not a valid command!")
                valid_solution = False
            elif not (R1 == R2 or C1 == C2):
                print(command + " in line " + str(i+2) + " is not a valid command!")
                valid_solution = False
            else:
                for r in (range(R1, R2+1) + range(R2, R1 + 1)):
                    for c in (range(C1, C2+1) + range(C2, C1+1)):
                        painted_image[r][c] = 1

    elif command[0] == 'ERASE_CELL':
        if not len(command) == 3:
            print(command + " in line " + str(i+2) + " is not a valid command!")
            valid_solution = False
        else:
            R, C = map(int, command[1:3])
            if not valid_coordinates(R, C):
                print(command + " in line " + str(i+2) + " is not a valid command!")
                valid_solution = False
            else:
                painted_image[R][C] = 0
    else:
        print(command + " in line " + str(i+2) + " is not a valid command!")
        valid_solution = False

    if valid_solution:
        for r in range(rows):
            for c in range(columns):
                if not image[r][c] == painted_image[r][c]:
                    valid_solution = False

    if valid_solution:
        print("The solution is valid and has a score of " + str(num_pixels - num_commands))
    else:
        print("The solution is not valid.")
