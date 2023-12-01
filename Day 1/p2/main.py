pattern = [
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
]

value = 0

with open("Day 1/p2/file.inp", "r") as f:
    for line in f.readlines():
        if line[-1] == '\n':
            line = line[:-1]
        df = -1
        pf = 9999999
        dl = -1
        pl = 0
        for idx, c in enumerate(line):
            if c.isdigit():
                if df == -1:
                    df = int(c)
                    pf = idx
                dl = int(c)
                pl = idx
        for idx, p in enumerate(pattern):
            fs = line.find(p)
            ls = line.rfind(p)
            if fs != -1 and fs < pf:
                pf = fs
                df = idx
            if ls != -1 and ls > pl:
                pl = ls
                dl = idx
        value += df * 10 + dl

with open("Day 1/p2/file.out", "w") as f:
    f.write(str(value))
        