
uint FUN_0082e863(uint param_1)

{
  uint uVar1;
  
  uVar1 = (int)param_1 >> 3 & 0x1f;
  if (uVar1 != 0) {
    param_1 = (param_1 & 7) + 8 << ((char)uVar1 - 1U & 0x1f);
  }
  return param_1;
}

