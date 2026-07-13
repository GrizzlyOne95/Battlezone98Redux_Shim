
void FUN_0080c3a0(undefined4 param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined1 local_38 [8];
  SchedulingNode local_30 [28];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00864ae8;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  FUN_00447eb0(param_1);
  cVar1 = FUN_0080ccc0(local_38);
  if (cVar1 == '\0') {
    uVar5 = 0;
    uVar4 = 0;
    uVar3 = FUN_00417780(param_1,0,0,uVar2);
    FUN_0080ccf0(uVar3,uVar4,uVar5);
    local_8 = 0;
    uVar3 = FUN_00417780(local_30);
    FUN_0080c4d0(uVar3);
    local_8 = 0xffffffff;
    Concurrency::details::SchedulingNode::~SchedulingNode(local_30);
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

