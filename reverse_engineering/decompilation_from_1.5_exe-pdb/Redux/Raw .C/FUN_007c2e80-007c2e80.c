
void FUN_007c2e80(undefined4 param_1)

{
  uint uVar1;
  undefined1 local_24 [8];
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084db68;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_1c = FUN_007d3ff0(local_24,param_1);
  local_8 = 0;
  local_18 = local_1c;
  FUN_00449910(local_1c);
  local_8 = 0xffffffff;
  FUN_004499a0(uVar1);
  *(uint *)(local_14 + 0x14) = *(uint *)(local_14 + 0x14) | 0x40000;
  ExceptionList = local_10;
  return;
}

