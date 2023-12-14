def score(b):
    row_count = len(b)
    col_count = len(b[0])
    ans = 0
    for r in range(row_count):
        for c in range(col_count):
            ans += (row_count - r) if b[r][c] == 'O' else 0
    return ans

def north(b):
    row_count = len(b)
    col_count = len(b[0])
    space = [0 for i in range(col_count)]
    for r in range(row_count):
        for c in range(col_count):
            if b[r][c] == '#':
                space[c] = 0
            if b[r][c] == '.':
                space[c] += 1
            if b[r][c] == 'O':
                b[r][c] = '.'
                b[r - space[c]][c] = 'O'
    return b

def west(b):
    row_count = len(b)
    col_count = len(b[0])
    space = [0 for i in range(row_count)]
    for c in range(col_count):
        for r in range(row_count):
            if b[r][c] == '#':
                space[r] = 0
            if b[r][c] == '.':
                space[r] += 1
            if b[r][c] == 'O':
                b[r][c] = '.'
                b[r][c - space[r]] = 'O'
    return b

def south(b):
    row_count = len(b)
    col_count = len(b[0])
    space = [0 for i in range(col_count)]
    for r in range(row_count - 1, -1, -1):
        for c in range(col_count):
            if b[r][c] == '#':
                space[c] = 0
            if b[r][c] == '.':
                space[c] += 1
            if b[r][c] == 'O':
                b[r][c] = '.'
                b[r + space[c]][c] = 'O'
    return b

def east(b):
    row_count = len(b)
    col_count = len(b[0])
    space = [0 for i in range(row_count)]
    for c in range(col_count - 1, -1, -1):
        for r in range(row_count):
            if b[r][c] == '#':
                space[r] = 0
            if b[r][c] == '.':
                space[r] += 1
            if b[r][c] == 'O':
                b[r][c] = '.'
                b[r][c + space[r]] = 'O'
    return b

def spin(b):
    return east(south(west(north(b))))

def get_key(b):
    k = ''
    for line in b:
        k = k + ''.join(line)
    return k


board = []

with open("file.inp", "r") as f:
    for line in f.readlines():
        board.append([])
        if line[-1] == '\n':
            line = line[:-1]
        for c in line:
            board[-1].append(c)

max_cycle = 1000000000
curr_key = get_key(board)
cache = {}
cycle = 0

while curr_key not in cache:
    cache[curr_key] = cycle
    board = spin(board)
    curr_key = get_key(board)
    cycle += 1

cycle_length = cycle - cache[curr_key]
for i in range(int((max_cycle - cycle) % cycle_length)):
    board = spin(board)


final_score = score(board)

with open("file.out", "w") as f:
    f.write(str(final_score))