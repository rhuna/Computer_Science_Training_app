import sys,collections,re
c=collections.Counter(re.findall(r"[A-Za-z0-9_]+", sys.stdin.read().lower()))
for k,v in c.items(): print(k,v)
