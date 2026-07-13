
void FUN_004d23f0(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int local_30 [2];
  undefined4 *local_28;
  char local_24 [16];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849fe0;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004812d0(param_1,param_2,param_3);
  local_8 = 0;
  *local_28 = FlamePuffClass::vftable;
  FUN_00589430(local_28 + 8);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00589800(0x8e290509,0x278d7166,local_28 + 0x1e,*(undefined4 *)(param_1 + 0x78));
  FUN_00589800(0x8e290509,0xc7dc5ce9,local_28 + 0x1f,*(undefined4 *)(param_1 + 0x7c));
  FUN_0047b6c0(0x8e290509,0xb051e2db,local_24,0);
  if (local_24[0] == '\0') {
    local_28[0x20] = *(undefined4 *)(param_1 + 0x80);
  }
  else {
    uVar1 = FUN_0068bed0(local_24);
    local_28[0x20] = uVar1;
  }
  FUN_00589760(0x8e290509,0x5d27caba,local_30,0);
  local_28[0x21] = local_28[0x20] + -1 + local_30[0];
  local_8 = local_8 & 0xffffff00;
  FUN_00589530();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

