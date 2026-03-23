
allocator<char> * __thiscall
FUN_006d8bb0(allocator<char> *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  void *local_18;
  allocator<char> *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085366c;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = param_1;
  std::allocator<char>::allocator<char>(param_1);
  local_8 = 0;
  FUN_006ac110(uVar2);
  local_8._0_1_ = 1;
  *(undefined4 *)(local_14 + 0x18) = param_2;
  local_18 = operator_new(0x5c);
  local_8._0_1_ = 2;
  if (local_18 == (void *)0x0) {
    local_1c = 0;
  }
  else {
    local_1c = FUN_006acec0(param_2,param_4);
  }
  local_20 = local_1c;
  local_8 = CONCAT31(local_8._1_3_,1);
  *(undefined4 *)(local_14 + 0x1c) = local_1c;
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)&local_28);
  FUN_006e7c20(&local_28,&DAT_02cc379e);
  iVar1 = *(int *)(local_14 + 0x1c);
  *(undefined4 *)(iVar1 + 4) = local_28;
  *(undefined4 *)(iVar1 + 8) = local_24;
  *(undefined4 *)(*(int *)(local_14 + 0x1c) + 0x10) = 0;
  ExceptionList = local_10;
  return local_14;
}

