
/* WARNING: Removing unreachable block (ram,0x008157e2) */

void FUN_008157a0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  char cVar1;
  int iVar2;
  undefined1 local_4c [12];
  undefined4 local_40;
  undefined1 local_35;
  SchedulingNode local_34 [32];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00864d58;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  iVar2 = FUN_007df2f0(local_14);
  if (iVar2 != 0) {
    local_40 = FUN_00417780(param_5);
    FUN_00815c20(local_34,local_40);
    local_8 = 0;
    FUN_007ef2f0(local_34);
    cVar1 = FUN_007ff0b0(param_1,param_2,local_4c,param_4);
    if (cVar1 == '\0') {
      FUN_007ff1f0(param_5,local_34);
      local_8 = 0xffffffff;
      Concurrency::details::SchedulingNode::~SchedulingNode(local_34);
    }
    else {
      FUN_00815c50(param_5,local_34);
      local_35 = 1;
      local_8 = 0xffffffff;
      Concurrency::details::SchedulingNode::~SchedulingNode(local_34);
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

