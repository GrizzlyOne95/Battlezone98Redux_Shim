
byte FUN_004ce390(byte param_1,byte param_2)

{
  char cVar1;
  undefined1 local_6;
  
  if ((param_1 < 0x30) || (0x39 < param_1)) {
    cVar1 = param_1 + 0xa9;
  }
  else {
    cVar1 = param_1 - 0x30;
  }
  if ((param_2 < 0x30) || (0x39 < param_2)) {
    local_6 = param_2 + 0xa9;
  }
  else {
    local_6 = param_2 - 0x30;
  }
  return cVar1 << 4 | local_6;
}

