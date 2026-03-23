
void FUN_006de830(undefined4 param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 in_stack_00000014;
  undefined1 local_cd [105];
  undefined1 local_64 [80];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00853c26;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  local_14 = uVar1;
  FUN_006e3cd0(in_stack_00000014);
  local_8._0_1_ = 1;
  local_cd[0] = 0;
  uVar2 = _String_const_iterator<>(uVar1);
  local_8._0_1_ = 2;
  FUN_006e3d40(param_1,&stack0x00000008,uVar2,local_cd,local_64);
  local_8._0_1_ = 3;
  uVar2 = 1;
  puVar3 = (undefined4 *)FUN_004fbb60(1);
  FUN_006e3de0(*puVar3,puVar3[1],uVar2);
  local_8._0_1_ = 2;
  FUN_006e0630();
  local_8._0_1_ = 1;
  FUN_006cd590();
  FUN_00417c60();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006e0610();
  local_8 = 0xffffffff;
  FUN_006cd590();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

