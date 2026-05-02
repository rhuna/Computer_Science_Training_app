import sys
l=sys.stdin.read().splitlines(); age=int(l[0]) if l else 0; email=l[1] if len(l)>1 else ""; user=l[2] if len(l)>2 else ""
print("valid" if age>=18 and "@" in email and len(user)>=3 else "invalid")
