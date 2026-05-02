import sys
n=int((sys.stdin.read().strip() or "42").split()[0])
print(bin(n)[2:])
print(hex(n)[2:].upper())
