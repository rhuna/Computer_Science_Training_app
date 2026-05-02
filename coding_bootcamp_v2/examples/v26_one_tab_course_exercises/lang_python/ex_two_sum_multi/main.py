import sys
l=sys.stdin.read().splitlines(); nums=list(map(int,(l[0] if l else "2 7 11 15").split())); target=int(l[1]) if len(l)>1 else 9
seen={}
for i,n in enumerate(nums):
    if target-n in seen: print(seen[target-n],i); break
    seen[n]=i
