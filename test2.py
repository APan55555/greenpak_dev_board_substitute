bytes_read = []

with open('bytes_read.txt', 'r') as f:
    bytes_read = f.readlines()

bits = []
for byte in bytes_read:
    bits.append(bin(int(byte))[2:])
res = ''
for bit in bits:
    padding = 8 - len(bit)
    for i in range(padding):
        res += '0\n'
    for bitbit in bit:
        res += bitbit + '\n'

with open('bits.txt', 'w') as f:
    f.write(res)