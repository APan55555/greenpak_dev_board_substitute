data = []
with open("data_read.txt", "r") as f:
    data = f.readlines()

bytes_read = []
counter = 0
ints = []
for i in range(10):
    ints.append(str(i))
for i in range(len(data)):
    if data[i][2] in ints:
        data[i] = data[i][2]
for thing in data:
    print(thing)
while counter < len(data):
    length = 1
    while counter + length < len(data) and (data[counter + length] in ints):
        length += 1
    bits = data[counter: counter + length]
    print(bits)
    res = 0
    for i in range(len(bits)):
        print(i, res, bits[i])
        res += int(bits[i]) * 10 ** (len(bits) - i - 1)
    bytes_read.append(res)
    counter += length
    while counter < len(data) and data[counter] not in ints:
        counter += 1

res = ''
for byte in bytes_read:
    res += str(byte) + '\n'
with open("bytes_read.txt", "w") as f:
    f.write(res);