
undefined4 * FUN_005da2d0(int param_1,undefined4 param_2,undefined4 param_3)

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
  puStack_c = &LAB_0084cb10;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0047ffd0(param_1,param_2,param_3);
  local_8 = 0;
  *local_14 = SprayBuildingClass::vftable;
  FUN_00589430(local_14 + 0xe);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00589c20(0x47523d0e,0x19d3ebc6,&local_20,0,0);
  if (local_20 == 0 && local_1c == 0) {
    local_14[0x58] = 0;
    FUN_007d6b70("SprayBuildingClass \"%s\" has no payload\n",local_14 + 0xe);
  }
  else {
    uVar2 = FUN_00586c60(local_20,local_1c,uVar1);
    local_14[0x58] = uVar2;
  }
  FUN_0047b6c0(0x47523d0e,0xcfde2fc0,local_14 + 0x59,param_1 + 0x164);
  FUN_00589800(0x47523d0e,0x682cd2b2,local_14 + 0x5d,*(undefined4 *)(param_1 + 0x174));
  FUN_00589800(0x47523d0e,0xd9356908,local_14 + 0x5e,*(undefined4 *)(param_1 + 0x178));
  FUN_00589800(0x47523d0e,0x4f358485,local_14 + 0x5f,*(undefined4 *)(param_1 + 0x17c));
  FUN_00589800(0x47523d0e,0x73accd30,local_14 + 0x60,*(undefined4 *)(param_1 + 0x17c));
  FUN_00589800(0x47523d0e,0x98902ade,local_14 + 0x61,*(undefined4 *)(param_1 + 0x184));
  local_8 = local_8 & 0xffffff00;
  FUN_00589530();
  ExceptionList = local_10;
  return local_14;
}

