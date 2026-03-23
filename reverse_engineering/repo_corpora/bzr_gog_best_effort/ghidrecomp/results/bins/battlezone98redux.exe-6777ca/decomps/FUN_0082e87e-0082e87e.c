
uint FUN_0082e87e(uint param_1)

{
  int iVar1;
  
  iVar1 = 0;
  for (; 0xf < param_1; param_1 = param_1 + 1 >> 1) {
    iVar1 = iVar1 + 1;
  }
  if (param_1 < 8) {
    return param_1;
  }
  return iVar1 * 8 + 8U | param_1 - 8;
}

