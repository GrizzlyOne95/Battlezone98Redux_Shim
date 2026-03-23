
void FUN_00834e28(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint local_218;
  uint *local_214 [131];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_0082ba59(param_1,1,&local_218);
  FUN_0082b98a(param_1,local_214);
  uVar3 = 0;
  if (local_218 != 0) {
    do {
      if (&local_8 <= local_214[0]) {
        FUN_0082c2ac(local_214);
      }
      iVar2 = tolower((uint)*(byte *)(uVar3 + iVar1));
      *(char *)local_214[0] = (char)iVar2;
      local_214[0] = (uint *)((int)local_214[0] + 1);
      uVar3 = uVar3 + 1;
    } while (uVar3 < local_218);
  }
  FUN_0082c2cb(local_214);
  FUN_0083e885();
  return;
}

