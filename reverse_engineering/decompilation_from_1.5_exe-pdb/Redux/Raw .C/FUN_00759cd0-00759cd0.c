
void FUN_00759cd0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined1 local_1c [16];
  undefined1 local_c [4];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_006b2f00();
  iVar1 = FUN_00759940(0x17,param_2,local_1c,local_c,param_3);
  if (iVar1 < 1) {
    FUN_006b2f00();
  }
  else {
    FUN_006b2f70(local_1c);
  }
  FUN_0083e885();
  return;
}

