import math
def extract_secret(filename):
    chunks = []
    with open(filename, 'rb') as f:
        f.read(13) 
        f.seek(10, 0)
        packed = ord(f.read(1))
        if packed & 0x80:
            n = packed & 0x07
            gct_size = 3 * int(math.pow(2, n + 1))
            f.seek(13 + gct_size, 0)
        else:
            f.seek(13, 0)
        while True:
            byte = f.read(1)
            if not byte: break
            b = ord(byte)
            if b == 0x3B:
                break

            elif b == 0x21:
                f.read(1)
                while True:
                    size = ord(f.read(1))
                    if size == 0: break
                    f.read(size)

            elif b == 0x2C:
                desc = f.read(9)
                chunks.append((desc[8] >> 4) & 0x03) # xxxyyxxx become 000000yy
                if desc[8] & 0x80:
                    lct_n = desc[8] & 0x07
                    lct_size = 3 * int(math.pow(2, lct_n + 1))
                    f.read(lct_size)

                f.read(1)
                while True:
                    size = ord(f.read(1))
                    if size == 0: break
                    f.read(size)
    return chunks

def reconstruct_message(chunks):
    bytes_list = []
    i = 0
    while i < len(chunks):
        if i + 3 >= len(chunks):
            break
        #bytes are recrafted 
        bits_8_7 = chunks[i] << 6
        bits_6_5 = chunks[i+1] << 4
        bits_4_3 = chunks[i+2] << 2
        bits_2_1 = chunks[i+3]

        valeur = bits_8_7 | bits_6_5 | bits_4_3 | bits_2_1
        bytes_list.append(valeur)
        i += 4
    data = bytearray(bytes_list).strip(b'\x00')
    return data.decode('utf-8')

if __name__ == "__main__":
    filename = "goofy_fantasy.gif"
    chunks = extract_secret(filename)
    secret = reconstruct_message(chunks)
    print(f"SECRET: {secret}")
