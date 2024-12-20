# Derived from https://cp-algorithms.com/string/manacher.html.
def solution(s: str) -> str:
    if len(s) <= 1:
        return s
    
    center = 0
    # Inclusive bounds on the current right-most palindrome.
    l, r = 0, 0
    # s' ("s prime")
    sp = "|" + "|".join(s) + "|"
    radii = [0] * len(sp)
    # print(f"{sp=}")

    while center < len(sp):
        # print(f"{center=}, {l=}, {r=}")
        if center < r:
            # We are within a palindrome. 
            mirrored_center = l + (r - center)
            # The `min` is necessary in cases like |o|n|o|n|a|n|, where center=7, l=2, r=8.
            # mirrored_center will be 3, which has radius 2, but that palindrome extends beyond the
            # current right-most palindrome.
            radius = min(radii[mirrored_center], r-center)
            # print(f"  In pal.; {mirrored_center=}, {radius=}")
        else:
            radius = 0

        # Subroutine shared with simple solution.
        left = center-(radius+1)
        right = center+(radius+1)
        while left > 0 and right < len(sp) and sp[left] == sp[right]:
            radius += 1
            left = center-(radius+1)
            right = center+(radius+1)
        # End subroutine

        # print(f"  final {radius=}")
        # radii.append(radius)
        radii[center] = radius

        if center + radius > r:
            l, r = center - radius, center + radius
            # print(f"  Changed right-most palindrome to {l}, {r}")

        center = center + 1
        
    # Shared with simple solution:
    max_radius = max(radii)
    center_of_largest = radii.index(max_radius)
    # print(f"{radii=}")
    # print(f"{sp=}")
    # print(f"{center_of_largest=}")
    # print(f"{max_radius=}")
    result = sp[center_of_largest-max_radius:center_of_largest+max_radius+1]
    return ''.join(filter(lambda c: c != "|", result))