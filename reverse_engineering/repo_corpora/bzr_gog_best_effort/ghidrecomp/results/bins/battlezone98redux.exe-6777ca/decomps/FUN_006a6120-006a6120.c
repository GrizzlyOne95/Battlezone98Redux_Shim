
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * FUN_006a6120(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  uint local_10;
  
  param_1 = DAT_00931018 + param_1;
  param_2 = DAT_00931020 + param_2;
  iVar2 = FUN_0077d640(param_1,param_2);
  _DAT_02c00aa8 = (int)(iVar2 + (iVar2 >> 0x1f & 0xfU)) >> 4;
  cVar1 = FUN_0046adb0(param_1,param_2);
  if (cVar1 == '\0') {
    local_10 = 3;
  }
  else {
    local_10 = FUN_0046acc0(param_1,param_2);
    local_10 = local_10 & 0xff;
  }
  _DAT_02c00aac = local_10;
  return &DAT_02c00a9c;
}

