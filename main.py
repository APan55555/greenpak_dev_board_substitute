import serial
from time import sleep

__name__ = 'main'

if __name__ == 'main':
    mem_lines = []
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
    
    mem_bytes = []
    counter = 0;
    while counter < len(bits):
        mem_byte = bits[counter]
        for bit_offset in range(1, 8):
            mem_byte = mem_byte << 1
            mem_byte += bits[counter + bit_offset]
        mem_bytes.append(mem_byte)
        counter += 8

    ser = serial.Serial("COM4", 9600)
    ser.setDTR()
    for byte in mem_bytes:
        while True:
            counter = 0
            ser.write((str(byte) + "\n").encode("raw_unicode_escape"))
            while ser.in_waiting == 0 and counter < 10:
                counter += 1
                sleep(0.001)
            if ser.in_waiting != 0:
                break
        ser.read()

    sleep(5);
    ser.write("h".encode("raw_unicode_escape"))
    while True:
        if ser.in_waiting != 0:
            print(ser.read())
