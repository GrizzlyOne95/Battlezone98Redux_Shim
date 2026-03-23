
void FUN_0080ce60(undefined4 param_1)

{
  undefined4 uVar1;
  SchedulingNode local_34 [32];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00854bb8;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar1 = FUN_006f9e20(param_1);
  local_8 = 0;
  FUN_00736ea0(uVar1);
  local_8 = 0xffffffff;
  Concurrency::details::SchedulingNode::~SchedulingNode(local_34);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

