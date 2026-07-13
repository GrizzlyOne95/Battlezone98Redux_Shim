
void __fastcall FUN_005abf70(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084c378;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = Producer::vftable;
  param_1[6] = Producer::vftable;
  local_8 = 0;
  _eh_vector_destructor_iterator_(param_1 + 0xd2,4,8,FUN_0044dc30);
  local_8 = 0xffffffff;
  FUN_004e9ef0(uVar1);
  ExceptionList = local_10;
  return;
}

