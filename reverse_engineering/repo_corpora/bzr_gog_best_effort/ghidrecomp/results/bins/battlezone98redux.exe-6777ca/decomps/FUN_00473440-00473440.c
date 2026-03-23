
undefined4 * FUN_00473440(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  undefined4 *local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008476f0;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_005b03c0(param_1,param_2,param_3);
  local_8 = 0;
  *local_18 = ArmoryClass::vftable;
  FUN_00589430(local_18 + 0xe);
  local_8 = CONCAT31(local_8._1_3_,1);
  for (local_14 = 0; local_14 < 9; local_14 = local_14 + 1) {
    uVar6 = 0;
    uVar5 = 0;
    piVar4 = &local_30;
    uVar3 = FUN_00446440(local_14 + 0x31,0x4549b5d3,piVar4,0,0,uVar2);
    FUN_00589c20(0xed18adf9,uVar3,piVar4,uVar5,uVar6);
    if (local_30 == 0 && local_2c == 0) {
      local_18[local_14 + 0x198] = 0;
    }
    else {
      uVar3 = FUN_004e0f70(local_30,local_2c);
      local_18[local_14 + 0x198] = uVar3;
    }
  }
  for (local_14 = 0; local_14 < 9; local_14 = local_14 + 1) {
    uVar6 = 0;
    uVar5 = 0;
    piVar4 = &local_38;
    uVar3 = FUN_00446440(local_14 + 0x31,0xae0b29d6,piVar4,0,0,uVar2);
    FUN_00589c20(0xed18adf9,uVar3,piVar4,uVar5,uVar6);
    if (local_38 == 0 && local_34 == 0) {
      local_18[local_14 + 0x1a1] = 0;
    }
    else {
      uVar3 = FUN_004e0f70(local_38,local_34);
      local_18[local_14 + 0x1a1] = uVar3;
    }
  }
  for (local_14 = 0; local_14 < 9; local_14 = local_14 + 1) {
    uVar6 = 0;
    uVar5 = 0;
    piVar4 = &local_28;
    uVar3 = FUN_00446440(local_14 + 0x31,0xd238f033,piVar4,0,0);
    FUN_00589c20(0xed18adf9,uVar3,piVar4,uVar5,uVar6);
    if (local_28 == 0 && local_24 == 0) {
      local_18[local_14 + 0x1aa] = 0;
    }
    else {
      uVar3 = FUN_004e0f70(local_28,local_24);
      local_18[local_14 + 0x1aa] = uVar3;
      if ((((local_18[local_14 + 0x1aa] != 0) && (cVar1 = FUN_00571c40(), cVar1 != '\0')) &&
          (local_20 = *(int *)(local_18[local_14 + 0x1aa] + 0x14), local_20 == 0x5745504e)) &&
         ((DAT_008e8c0c == '\0' &&
          (((local_28 == 0x70737061 && (local_24 == 0x6e6c)) ||
           ((local_28 == 0x70737073 && (local_24 == 0x6e6c)))))))) {
        local_18[local_14 + 0x1aa] = 0;
      }
    }
  }
  for (local_14 = 0; local_14 < 9; local_14 = local_14 + 1) {
    uVar6 = 0;
    uVar5 = 0;
    piVar4 = &local_40;
    uVar3 = FUN_00446440(local_14 + 0x31,0xe01161ff,piVar4,0,0);
    FUN_00589c20(0xed18adf9,uVar3,piVar4,uVar5,uVar6);
    if (local_40 == 0 && local_3c == 0) {
      local_18[local_14 + 0x1b3] = 0;
    }
    else {
      uVar3 = FUN_004e0f70(local_40,local_3c);
      local_18[local_14 + 0x1b3] = uVar3;
    }
  }
  local_8 = local_8 & 0xffffff00;
  FUN_00589530();
  ExceptionList = local_10;
  return local_18;
}

