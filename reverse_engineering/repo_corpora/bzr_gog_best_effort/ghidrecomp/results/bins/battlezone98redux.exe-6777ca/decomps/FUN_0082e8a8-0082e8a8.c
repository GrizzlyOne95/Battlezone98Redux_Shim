
int FUN_0082e8a8(uint param_1)

{
  int iVar1;
  
  iVar1 = -1;
  for (; 0xff < param_1; param_1 = param_1 >> 8) {
    iVar1 = iVar1 + 8;
  }
  return (uint)*(byte *)((int)&PTR_DAT_0086ed28 + param_1) + iVar1;
}

