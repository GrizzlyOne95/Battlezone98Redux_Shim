
void FUN_00834d75(undefined4 param_1)

{
  int iVar1;
  int local_218;
  uint *local_214 [131];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_0082ba59(param_1,1,&local_218);
  FUN_0082b98a(param_1,local_214);
  while (local_218 != 0) {
    local_218 = local_218 + -1;
    if (&local_8 <= local_214[0]) {
      FUN_0082c2ac(local_214);
    }
    *(undefined1 *)local_214[0] = *(undefined1 *)(local_218 + iVar1);
    local_214[0] = (uint *)((int)local_214[0] + 1);
  }
  local_218 = -1;
  FUN_0082c2cb(local_214);
  FUN_0083e885();
  return;
}

