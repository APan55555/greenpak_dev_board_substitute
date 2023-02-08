with open('input.txt', 'r') as f:
    mem_lines = f.readlines()
del mem_lines[0]

bits = []
for line in mem_lines:
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

bits_read = []
with open('bits.txt', 'r') as f:
    bits_read = [int(x) for x in f.readlines()]

for i in range(len(bits_read)):
    if bits_read[i] != bits[i]:
        print(i, bits_read[i])