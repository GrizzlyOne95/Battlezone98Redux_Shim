
undefined4 __thiscall FUN_0072d7f0(undefined4 param_1,int param_2)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00859b48;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar2 = std::allocator<char>::allocator<char>((allocator<char> *)(param_2 + 4));
  uVar2 = FUN_00417780(uVar2,uVar1);
  uVar3 = FUN_006d0d10(uVar2);
  uVar3 = FUN_00417780(uVar3);
  _Vector_iterator<>(uVar3,uVar2);
  local_8 = 0;
  FUN_0071ff00(param_2);
  ExceptionList = local_10;
  return param_1;
}

