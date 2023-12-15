focal = {}
hashmap = [[] for i in range(256)]

def hashing(original_value, character):
    return int(((original_value + ord(character)) * 17) % 256)

def main():
    inp_file = ""
    with open("file.inp", "r") as f:
        inp_file = f.readlines()[0]
        if inp_file[-1] == '\n':
            inp_file = inp_file[:-1]
    
    mode = 0 # 0 = read, 1 = set, 2 = remove
    current_name = ''
    current_hash = 0
    read_value = ''
    for c in inp_file:
        if c == '=':
            mode = 1
        elif c == '-':
            mode = 2
        elif c == ',':
            if mode == 1:
                if current_name not in hashmap[current_hash]:
                    hashmap[current_hash].append(current_name)
                focal[current_name] = int(read_value)
            elif mode == 2:
                if current_name in hashmap[current_hash]:
                    hashmap[current_hash].remove(current_name)
            current_hash = 0
            current_name = ''
            read_value = ''
            mode = 0
        else:
            if mode == 0:
                current_hash = hashing(current_hash, c)
                current_name = current_name + c
            elif mode == 1:
                read_value = read_value + c 

    
    if mode == 1:
        if current_name not in hashmap[current_hash]:
            hashmap[current_hash].append(current_name)
        focal[current_name] = int(read_value)
    elif mode == 2:
        if current_name in hashmap[current_hash]:
            hashmap[current_hash].remove(current_name)
    current_hash = 0
    current_name = ''
    read_value = ''
    mode = 0

    ans = 0
    for box in range(256):
        for idx, lens in enumerate(hashmap[box]):
            ans += (box + 1) * (idx + 1) * focal[lens]
    
    with open("file.out", 'w') as f:
        f.write(str(ans))

if __name__ == "__main__":
    main()