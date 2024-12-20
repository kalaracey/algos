def solution(s: str) -> str:
    if len(s) <= 1:
        return s

    radii = []
    center = 0
    # s' ("s prime")
    sp = "|" + "|".join(s) + "|"

    while center < len(sp):
        radius = 0
        left = center-(radius+1)
        right = center+(radius+1)
        while left > 0 and right < len(sp) and sp[left] == sp[right]:
            radius += 1
            left = center-(radius+1)
            right = center+(radius+1)

        radii.append(radius)
        center = center + 1

    max_radius = max(radii)
    center_of_largest = radii.index(max_radius)
    # print(f"{sp=}")
    # print(f"{center_of_largest=}")
    # print(f"{radius=}")
    result = sp[center_of_largest-max_radius:center_of_largest+max_radius+1]
    return ''.join(filter(lambda c: c != "|", result))

            
