
undefined4 * FUN_006123a0(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int local_2c;
  int local_28;
  int local_24;
  uint local_20;
  undefined4 local_1c;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084d2a0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00511720(param_1,param_2,param_3);
  local_8 = 0;
  *local_14 = WeaponMineClass::vftable;
  FUN_00589430(local_14 + 0xe);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00589800(0x47d843ca,0xe3635ff7,local_14 + 0x5a,*(undefined4 *)(param_1 + 0x168));
  FUN_00589800(0x47d843ca,0xcaaa3778,local_14 + 0x5b,*(undefined4 *)(param_1 + 0x16c));
  FUN_00589c20(0x47d843ca,0xfbf47dba,&local_2c,0,0);
  if (local_2c == 0 && local_28 == 0) {
    local_14[0x5c] = *(undefined4 *)(param_1 + 0x170);
  }
  else {
    uVar1 = FUN_00611e30(local_2c,local_28);
    local_14[0x5c] = uVar1;
  }
  if (((local_14[0x5c] == 0) || (*(int *)(local_14[0x5c] + 0xc) == 0x44495350)) ||
     (*(int *)(local_14[0x5c] + 0xc) == 0x5244524c)) {
    local_1c = 0;
  }
  else {
    local_1c = 1;
  }
  FUN_00589760(0x47d843ca,0xb30f7ac,&local_24,local_1c);
  local_20 = (uint)(local_24 != 0);
  *(bool *)(local_14 + 0x5d) = local_24 != 0;
  local_8 = local_8 & 0xffffff00;
  FUN_00589530();
  ExceptionList = local_10;
  return local_14;
}

