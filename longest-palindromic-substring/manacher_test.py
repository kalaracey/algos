import hypothesis.strategies as st
from hypothesis import Verbosity, given, settings

import manacher
import simple


def test_ononan():
    s = "ononan"
    assert manacher.solution(s) == simple.solution(s)

@given(st.text(alphabet=st.characters(min_codepoint=ord('a'), max_codepoint=ord('z')), 
               min_size=5, max_size=10))
@settings(max_examples=100000)
def test_manacher(x: str):
    result = manacher.solution(x)
    alt = simple.solution(x)
    assert result == alt
    # if len(alt) > 1:
    #     print(f"{x}: {alt}")
