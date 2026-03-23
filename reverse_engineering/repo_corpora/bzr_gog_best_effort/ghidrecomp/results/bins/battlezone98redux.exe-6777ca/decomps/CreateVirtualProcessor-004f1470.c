
/* Library Function - Multiple Matches With Same Base Name
    public: virtual class Concurrency::details::VirtualProcessor * __thiscall
   Concurrency::details::ThreadScheduler::CreateVirtualProcessor(class
   Concurrency::details::SchedulingNode *,struct Concurrency::IVirtualProcessorRoot *)
    public: virtual class Concurrency::details::VirtualProcessor * __thiscall
   Concurrency::details::UMSThreadScheduler::CreateVirtualProcessor(class
   Concurrency::details::SchedulingNode *,struct Concurrency::IVirtualProcessorRoot *)
   
   Library: Visual Studio 2010 Debug */

undefined4 __thiscall CreateVirtualProcessor(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084752b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = FUN_004d9f90(0x378,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  if (iVar1 == 0) {
    local_18 = 0;
  }
  else {
    local_18 = FUN_004f0d40(param_2,param_1);
  }
  ExceptionList = local_10;
  return local_18;
}

