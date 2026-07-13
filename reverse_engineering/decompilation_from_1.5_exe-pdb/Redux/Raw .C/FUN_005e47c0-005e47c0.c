
void __fastcall FUN_005e47c0(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_50 [16];
  undefined4 local_40;
  undefined1 local_24 [4];
  undefined4 local_20;
  undefined4 local_18;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = *(int *)(param_1 + 0xf8);
  if ((*(char *)(iVar1 + 0x19c) != '\0') && (*(int *)(param_1 + 0x234) == 0)) {
    FUN_0043a990(local_50);
    local_40 = 0x4001;
    FUN_0043a9e0(local_24);
    local_18 = 1;
    if ((*(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0x10) == 0) {
      local_20 = 0x2d;
    }
    else {
      local_20 = 0x41;
    }
    uVar2 = FUN_0043aa30(iVar1 + 0x19c,*(undefined4 *)(param_1 + 0xf4),local_50,local_24);
    *(undefined4 *)(param_1 + 0x234) = uVar2;
  }
  FUN_0083e885();
  return;
}

