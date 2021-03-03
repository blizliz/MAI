s = "anagram"
t = "nagaram"

def isAnagram(s, t):
    for ch in s:
        print(ch)
        inx = t.index(ch)
        print(inx)
        if inx:
            t = t[: inx] + t[inx + 1 :]
        else:
            return False
        print(t)
            
    if t:
        return False
    else:
        return True

print(isAnagram(s, t))

p = "aaaa"
inx = p.index("b")
print(inx)
