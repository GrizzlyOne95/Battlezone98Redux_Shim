
void FUN_00573090(undefined4 param_1,short param_2,undefined1 param_3)

{
  int iVar1;
  undefined2 local_18;
  undefined1 local_16;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (param_2 != 0) {
    local_18 = 0x4b50;
    local_16 = param_3;
    iVar1 = FUN_007659f0();
    if (iVar1 != 0) {
      FUN_007596b0(param_2,&local_18,3,1);
    }
  }
  FUN_0083e885();
  return;
}

