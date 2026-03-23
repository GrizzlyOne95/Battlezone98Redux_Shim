
bool FUN_0082de36(uint param_1)

{
  uint uVar1;
  
  uVar1 = param_1 & 0x3f;
  if ((0x1b < uVar1) && ((uVar1 < 0x1f || (uVar1 == 0x22)))) {
    return (param_1 & 0xff800000) == 0;
  }
  return false;
}

