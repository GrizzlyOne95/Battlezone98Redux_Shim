
void __fastcall FUN_00800170(int param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00845ab8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  Concurrency::details::SchedulingNode::~SchedulingNode((SchedulingNode *)(param_1 + 0x18));
  local_8 = 0xffffffff;
  ~basic_string<>(uVar1);
  ExceptionList = local_10;
  return;
}

