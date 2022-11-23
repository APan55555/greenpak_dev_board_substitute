__name__ = 'main'

if __name__ == 'main':
    mem_lines = []
    with open('input.txt', 'r') as f:
        mem_lines = f.readlines()
    del mem_lines[0]

    bits = []
    for line in mem_lines:
        print(line)
        bit = 0
        counter = len(line) - 1
        while counter > 0:
            if line[counter] == '0':
                bit = 0
                break
            if line[counter] == '1':
                bit = 1
                break
            counter -= 1
        bits.append(bit)
    
    mem_bytes = []
    counter = 0;
    while counter < len(bits):
        mem_byte = bits[counter]
        for bit_offset in range(1, 8):
            mem_byte = mem_byte << 1
            mem_byte += bits[counter + bit_offset]
        mem_bytes.append(mem_byte)
        counter += 8

    for mem_byte in mem_bytes:
        print(bin(mem_byte))
