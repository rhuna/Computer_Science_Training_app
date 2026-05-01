def convert(n, base):
    digits = "0123456789ABCDEF"
    if n == 0:
        return "0"
    out = ""
    while n > 0:
        out = digits[n % base] + out
        n //= base
    return out

n = int(input().strip() or "42")
print("binary", convert(n, 2))
print("hex", convert(n, 16))
