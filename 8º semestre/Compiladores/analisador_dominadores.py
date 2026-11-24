verticies=['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm']

D = {
    'a': set(['a']),
    'b': set(verticies),
    'c': set(verticies),
    'd': set(verticies),
    'e': set(verticies),
    'f': set(verticies),
    'g': set(verticies),
    'h': set(verticies),
    'i': set(verticies),
    'j': set(verticies),
    'k': set(verticies),
    'l': set(verticies),
    'm': set(verticies)
}

pred = {
    "a": {""},
    "b": {"a", "g"},
    "c": {"a", "j"},
    "d": {"b", "h"},
    "e": {"c"},
    "f": {"c"},
    "g": {"d"},
    "h": {"d"},
    "i": {"h", "e"},
    "j": {"f", "i"},
    "k": {"g"},
    "l": {"k", "m"},
    "m": {"e", "i"},
}

idom = {"a": "-"}

it = 0;
while True:
    it += 1
    print(f"Iteracao: {it}")
    
    [print(f"D[{key}]:{D[key]}") for key in D]
    Dcopia=D.copy()
    for key in "bcdefghijklm":
        inter=set(verticies)
        for l in pred[key]:
            inter &= D[l]
        D[key] =  {key} | inter
        
        """
        for d in D[key] - {key}:
            if d != key:
                idom[key] = d
                break
            else:
                idom[key] = "-"
        """
    print("\n\n")
    if Dcopia==D:
        print("Convergencia atingida")
        [print(f"idom[{key}]:{idom[key]}") for key in idom]
        """
        Slide 355 (explicação)
        a -
        b a
        c a
        d b
        e c
        f c
        g d
        h d
        i a
        j a
        k g
        l a
        m a
        """
        break