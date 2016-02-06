import sys

# example usage
#     $ python validate.py right_angle.in right_angle.txt

image_name = sys.argv[1]
command_file_name = sys.argv[2]

image = file(image_name).read()
commands = file(command_file_name).read()

def parse_image(image):
    lines = image.split('\n')
    M, N = map(int, lines[0].split())
    img = lines[1:-1]
    return M, N, img

def parse_commands(commands):
    lines = commands.split('\n')
    TT = int(lines[0])
    cmds = lines[1:-1]
    assert len(cmds) == TT
    return cmds

M, N, img = parse_image(image)

cmds = parse_commands(commands)

result = []
for r in range(M):
    row = []
    for c in range(N):
        row.append('.')
    result.append(row)

for c in cmds:
    cmd = c.split()
    word = cmd[0]
    nums = map(int, cmd[1:])
    if word == 'PAINT_SQUARE':
        R, C, S = nums
        for x in range(R-S, R+S+1):
            for y in range(C-S, C+S+1):
                result[x][y] = '#'
    elif word == "PAINT_LINE":
        x0, y0, x1, y1 = nums
        assert (x1-x0) * (y1-y0) == 0
        for x in range(x0, x1+1):
            for y in range(y0, y1+1):
                result[x][y] = '#'
    elif word == "ERASE_CELL":
        x, y = nums
        result[x][y] = '.'
    else:
        raise ValueError

for x in range(M):
    for y in range(N):
        if result[x][y] != img[x][y]:
            print "problem at {} {}".format(x,y)

print "validation complete!"
