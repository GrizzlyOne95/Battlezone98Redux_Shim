
void FUN_0071a9d0(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  CCachedDataPathProperty local_b4 [160];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008584db;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar1 = FUN_0071dba0(param_1,param_2 + 8);
  local_8 = 0;
  FUN_007251d0(uVar1);
  local_8 = 0xffffffff;
  CCachedDataPathProperty::~CCachedDataPathProperty(local_b4);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

