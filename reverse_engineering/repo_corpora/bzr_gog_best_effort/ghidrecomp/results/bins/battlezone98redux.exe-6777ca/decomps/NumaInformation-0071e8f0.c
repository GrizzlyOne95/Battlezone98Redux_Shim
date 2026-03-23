
/* Library Function - Single Match
    public: __thiscall Concurrency::details::SchedulerBase::NumaInformation::NumaInformation(void)
   
   Libraries: Visual Studio 2012, Visual Studio 2015, Visual Studio 2017, Visual Studio 2019 */

NumaInformation * __thiscall
Concurrency::details::SchedulerBase::NumaInformation::NumaInformation(NumaInformation *this)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008588d8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068b0a0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  QuickBitSet::QuickBitSet((QuickBitSet *)(this + 0xc));
  ExceptionList = local_10;
  return this;
}

