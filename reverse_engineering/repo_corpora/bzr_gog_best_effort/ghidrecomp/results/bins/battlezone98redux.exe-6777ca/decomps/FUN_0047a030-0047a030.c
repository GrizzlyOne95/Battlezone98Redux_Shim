
void __thiscall FUN_0047a030(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  char local_24 [16];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00847900;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004812d0(param_2,param_3,param_4);
  local_8 = 0;
  *param_1 = BeamClass::vftable;
  FUN_00589430(param_1 + 8);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00589800(0xf18c83ca,0x74a4cc84,param_1 + 0x1e,*(undefined4 *)(param_2 + 0x78));
  FUN_00589800(0xf18c83ca,0x97bf6bf2,param_1 + 0x1f,*(undefined4 *)(param_2 + 0x7c));
  FUN_00589800(0xf18c83ca,0xc01fedb1,param_1 + 0x20,*(undefined4 *)(param_2 + 0x80));
  FUN_0047b6c0(0xf18c83ca,0xe30fe0e9,local_24,0);
  if (local_24[0] == '\0') {
    param_1[0x21] = 0;
  }
  else {
    uVar1 = FUN_0068bed0(local_24);
    param_1[0x21] = uVar1;
  }
  local_8 = local_8 & 0xffffff00;
  FUN_00589530();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

