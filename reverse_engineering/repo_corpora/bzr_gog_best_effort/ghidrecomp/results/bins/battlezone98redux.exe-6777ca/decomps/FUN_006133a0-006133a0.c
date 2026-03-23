
undefined4 * FUN_006133a0(int param_1,undefined4 param_2,undefined4 param_3)

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
  puStack_c = &LAB_0084d2d0;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_005ab360(param_1,param_2,param_3);
  local_8 = 0;
  *local_14 = WeaponPowerupClass::vftable;
  FUN_00589430(local_14 + 0xe);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00589c20(0x397a9ac1,0xfbf47dba,&local_20,0,0);
  if (local_20 == 0 && local_1c == 0) {
    local_14[0x5c] = *(undefined4 *)(param_1 + 0x170);
  }
  else {
    uVar2 = FUN_00611e30(local_20,local_1c,uVar1);
    local_14[0x5c] = uVar2;
    if (*(char *)(local_14[0x5c] + 0x38) != '\0') {
      strncpy((char *)(local_14 + 0x19),(char *)(local_14[0x5c] + 0x38),0x20);
    }
  }
  local_8 = local_8 & 0xffffff00;
  FUN_00589530();
  ExceptionList = local_10;
  return local_14;
}

