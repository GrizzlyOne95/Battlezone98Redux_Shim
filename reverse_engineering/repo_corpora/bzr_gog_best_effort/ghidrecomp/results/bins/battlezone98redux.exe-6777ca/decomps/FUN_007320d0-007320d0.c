
void FUN_007320d0(undefined4 param_1,int param_2)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00859ecb;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar2 = FUN_00732fc0(param_1,param_2 + 8);
  local_8 = 0;
  FUN_00733ae0(uVar2);
  local_8 = 0xffffffff;
  FID_conflict___CancellationTokenCallback<class_<lambda_61f7764e5b8087545c74b0c2f4f68b12>_>(uVar1);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

