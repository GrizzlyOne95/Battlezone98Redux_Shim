
undefined4 * FUN_005b14d0(int param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  int local_20;
  int local_1c;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c3e0;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004caf20(param_1,param_2,param_3);
  local_8 = 0;
  *local_14 = QuakeBlastClass::vftable;
  FUN_00589430(local_14 + 6);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00589760(0x8630865c,0x46b7241d,local_14 + 0x9c,*(undefined4 *)(param_1 + 0x270));
  FUN_00589c20(0x8630865c,0x3bc0709e,&local_20,0,0);
  if (local_20 == 0 && local_1c == 0) {
    local_14[0x9d] = *(undefined4 *)(param_1 + 0x274);
  }
  else {
    uVar2 = FUN_00586c60(local_20,local_1c,uVar1);
    local_14[0x9d] = uVar2;
  }
  FUN_00589800(0x8630865c,0x5dab2378,local_14 + 0x9e,*(undefined4 *)(param_1 + 0x278));
  local_8 = local_8 & 0xffffff00;
  FUN_00589530();
  ExceptionList = local_10;
  return local_14;
}

