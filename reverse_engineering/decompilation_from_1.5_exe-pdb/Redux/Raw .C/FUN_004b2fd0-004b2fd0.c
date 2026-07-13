
undefined4 __fastcall FUN_004b2fd0(undefined4 param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_12;
  allocator<char> local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849878;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar2 = std::allocator<char>::allocator<char>(&local_11);
  FUN_004239a0(&local_12,uVar2);
  local_8 = 0;
  uVar2 = FUN_00416410(uVar1);
  uVar3 = get(uVar2);
  FUN_004b3360(uVar3,uVar2);
  ExceptionList = local_10;
  return param_1;
}

