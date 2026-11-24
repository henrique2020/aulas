pred = [[],[],[1,6],[2],[3],[3],[4,5],[2]]
FD = [set() for _ in range(8)]
idom = [0,0,1,2,3,3,3,2]
for b in range(1,8):
    if len(pred[b])>=2:
        for p in pred[b]:
            runner = p
            while runner!=idom[b]:
                FD[runner].add(b)
                runner = idom[runner]
print(FD[1:])