
undefined4 FUN_00764bc0(void)

{
  ushort uVar1;
  HMODULE pHVar2;
  int *piVar3;
  int iVar4;
  char *local_28;
  int local_24;
  void *local_14;
  code *pcStack_10;
  uint local_c;
  undefined4 local_8;
  
  local_8 = 0xfffffffe;
  pcStack_10 = FUN_0083f1c9;
  local_14 = ExceptionList;
  local_c = DAT_008e7000 ^ 0x8cf8b8;
  ExceptionList = &local_14;
  if (DAT_02cc2c84 == 0) {
    pHVar2 = GetModuleHandleA((LPCSTR)0x0);
    piVar3 = (int *)((int)&pHVar2->unused + pHVar2[0xf].unused);
    if (*piVar3 == 0x4550) {
      local_8 = 0xfffffffe;
      local_28 = (char *)((int)piVar3 + *(ushort *)(piVar3 + 5) + 0x18);
      uVar1 = *(ushort *)((int)piVar3 + 6);
      for (local_24 = 1; local_24 <= (int)(uint)uVar1; local_24 = local_24 + 1) {
        iVar4 = strncmp(local_28,".bind",6);
        if (iVar4 == 0) {
          DAT_02cc2c80 = 1;
          DAT_02cc2c84 = 1;
          ExceptionList = local_14;
          return 1;
        }
        local_28 = local_28 + 0x28;
      }
      DAT_02cc2c84 = 1;
      DAT_02cc2c80 = 0;
    }
    else {
      DAT_02cc2c84 = 1;
      DAT_02cc2c80 = 0;
    }
  }
  ExceptionList = local_14;
  return DAT_02cc2c80;
}

