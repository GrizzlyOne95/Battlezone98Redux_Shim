
undefined4 __thiscall FUN_006f1a70(undefined4 param_1,allocator<char> *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008550e8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar2 = std::allocator<char>::allocator<char>(param_2);
  uVar2 = FUN_00417780(uVar2,uVar1);
  FUN_006feb50(uVar2);
  local_8 = 0;
  uVar2 = FUN_00417780(param_2 + 0x28);
  FID_conflict__Callable_obj<class_<lambda_9ab38a79c03e1e04423ad6818173354b>,0><class_<lambda_9ab38a79c03e1e04423ad6818173354b>_>
            (uVar2);
  ExceptionList = local_10;
  return param_1;
}

