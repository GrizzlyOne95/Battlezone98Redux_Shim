file(READ "${INPUT}" bytes HEX)
string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," array "${bytes}")
file(WRITE "${OUTPUT}" "#pragma once\ninline constexpr unsigned char ${SYMBOL}[] = {${array}};\n")
