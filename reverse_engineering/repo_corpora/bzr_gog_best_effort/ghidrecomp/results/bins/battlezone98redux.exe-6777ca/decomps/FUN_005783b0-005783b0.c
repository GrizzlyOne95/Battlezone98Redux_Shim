
/* WARNING: Removing unreachable block (ram,0x00578482) */

void FUN_005783b0(void)

{
  int iVar1;
  char *_Source;
  uint uVar2;
  size_t _Count;
  int local_38;
  undefined1 local_30;
  undefined1 local_2f;
  undefined2 local_2e;
  undefined1 local_2c;
  char acStack_2b [32];
  undefined1 uStack_b;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_00578380();
  if (iVar1 != 0) {
    local_30 = 0x7a;
    local_2f = 0x4c;
    local_2e = *(undefined2 *)(iVar1 + 0x28);
    local_2c = *(undefined1 *)(iVar1 + 0x68);
    _Count = 0x20;
    _Source = (char *)FUN_0041f870();
    strncpy(acStack_2b,_Source,_Count);
    uVar2 = FUN_004170c0();
    if (uVar2 < 0x21) {
      local_38 = FUN_004170c0();
      local_38 = local_38 + 6;
    }
    else {
      local_38 = 0x26;
    }
    uStack_b = 0;
    FUN_00575890(&local_30,local_38,1,1);
  }
  FUN_0083e885();
  return;
}

