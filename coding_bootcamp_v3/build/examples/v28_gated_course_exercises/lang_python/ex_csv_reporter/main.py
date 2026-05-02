import sys,csv,io
rows=list(csv.DictReader(io.StringIO(sys.stdin.read()))); vals=[int(r["value"]) for r in rows]
print(sum(vals)); print(max(vals)); print(len(vals))
