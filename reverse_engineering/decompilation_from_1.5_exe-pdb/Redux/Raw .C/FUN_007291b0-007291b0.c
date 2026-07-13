
undefined4 FUN_007291b0(undefined4 param_1)

{
  undefined4 uVar1;
  int in_stack_00000014;
  int in_stack_00000018;
  uint uStack_144;
  undefined1 auStack_134 [108];
  undefined1 local_c8 [84];
  undefined4 uStack_74;
  undefined4 local_70;
  undefined4 uStack_6c;
  undefined4 local_48;
  uint local_28;
  undefined4 local_20;
  uint local_1c;
  int local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00859571;
  local_10 = ExceptionList;
  uStack_144 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_144;
  ExceptionList = &local_10;
  local_28 = 0;
  local_8 = 0;
  local_70 = FUN_004bb540(local_c8);
  local_8._0_1_ = 1;
  local_48 = local_70;
  local_1c = FUN_00726690(local_70);
  local_8._0_1_ = 0;
  FUN_004bb3b0();
  local_20 = *(undefined4 *)(local_18 + 0x10);
  if (in_stack_00000014 == in_stack_00000018) {
    uStack_74 = FUN_004bb540(auStack_134);
    local_8._0_1_ = 0x12;
    uStack_6c = uStack_74;
    FID_conflict_operator_(param_1,local_1c);
    local_28 = local_28 | 1;
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_004bb3b0();
    local_8 = 0xffffffff;
    FUN_004bb3d0();
    ExceptionList = local_10;
    return param_1;
  }
  if (local_1c <= *(uint *)(local_18 + 0x10) >> 1) {
    local_8 = CONCAT31(local_8._1_3_,2);
    for (; in_stack_00000014 != in_stack_00000018; in_stack_00000014 = in_stack_00000014 + 1) {
      FUN_00726350(in_stack_00000014);
    }
    uVar1 = FUN_0072929c();
    return uVar1;
  }
  local_8 = CONCAT31(local_8._1_3_,10);
  for (; in_stack_00000014 != in_stack_00000018; in_stack_00000014 = in_stack_00000014 + 1) {
    FUN_00726500(in_stack_00000014);
  }
  uVar1 = FUN_00729476();
  return uVar1;
}

