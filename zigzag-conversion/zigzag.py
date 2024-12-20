import itertools


def solution(self, s: str, numRows: int) -> str:
    if len(s) < 1:
        return s

    # P   A   H   N
    # A P L S I I G
    # Y   I   R
    #
    # 0, 4, 8, 12            -- gaps of 4/0  (4-2*0 and 2*0) 
    # 1, 3, 5, 7, 9, 11, 13  -- gaps of 2/2  (4-2*1 and 2*1)
    # 2, 6, 10, (14)         -- gaps of 0/4  (4-2*2 and 2*2)

    # P     I    N
    # A   L S  I G
    # Y A   H R
    # P     I
    #
    # 0, 6, 12          -- gaps of 6/0
    # 1, 5, 7, 11, 13   -- gaps of 4/2 (6-2*1 and 2*1)
    # 2, 4, 8, 10, (14) -- gaps of 2/4 (6-2*2 and 2*2)
    # 3, 9, (15)        -- gaps of 0/6
    
    row = 0
    result = ""
    gap = 0 if numRows < 3 else numRows - 2
    while row < numRows:
        i = row
        increment = itertools.cycle([x for x in [numRows + gap - 2*row, 2*row] if x != 0])
        while i < len(s):
            result += s[i]
            i += next(increment)
        row += 1

    return result
