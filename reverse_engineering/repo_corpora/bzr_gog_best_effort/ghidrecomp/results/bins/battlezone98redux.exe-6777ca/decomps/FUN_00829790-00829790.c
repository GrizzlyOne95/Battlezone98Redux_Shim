
undefined4 __thiscall FUN_00829790(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 local_12;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00864ba8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar2 = Getal(&local_12);
  allocator<>(uVar2);
  FUN_00829b40(&local_11);
  local_8 = 0;
  uVar2 = FUN_00417780(param_2,uVar1);
  FUN_0080f250(uVar2);
  ExceptionList = local_10;
  return param_1;
}

