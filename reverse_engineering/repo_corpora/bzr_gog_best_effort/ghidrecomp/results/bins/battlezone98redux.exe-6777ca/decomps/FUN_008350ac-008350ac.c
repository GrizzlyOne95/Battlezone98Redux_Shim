
void FUN_008350ac(undefined4 param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint *local_214 [131];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_0082c8f6(param_1);
  FUN_0082b98a(param_1,local_214);
  iVar3 = 1;
  if (0 < iVar1) {
    do {
      uVar2 = FUN_0082ba1c(param_1,iVar3);
      if ((uVar2 & 0xff) != uVar2) {
        FUN_0082b8e4(param_1,iVar3,"invalid value");
      }
      if (&local_8 <= local_214[0]) {
        FUN_0082c2ac(local_214);
      }
      *(char *)local_214[0] = (char)uVar2;
      local_214[0] = (uint *)((int)local_214[0] + 1);
      iVar3 = iVar3 + 1;
    } while (iVar3 <= iVar1);
  }
  FUN_0082c2cb(local_214);
  FUN_0083e885();
  return;
}

