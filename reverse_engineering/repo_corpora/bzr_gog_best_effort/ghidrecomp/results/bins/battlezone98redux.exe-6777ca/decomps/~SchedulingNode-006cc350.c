
/* Library Function - Single Match
    public: __thiscall Concurrency::details::SchedulingNode::~SchedulingNode(void)
   
   Library: Visual Studio 2010 Debug */

void __thiscall Concurrency::details::SchedulingNode::~SchedulingNode(SchedulingNode *this)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00852adb;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_006d0c90(DAT_008e7000 ^ (uint)&stack0xfffffffc,this);
  local_8 = 0xffffffff;
  FUN_00417c60();
  ExceptionList = local_10;
  return;
}

