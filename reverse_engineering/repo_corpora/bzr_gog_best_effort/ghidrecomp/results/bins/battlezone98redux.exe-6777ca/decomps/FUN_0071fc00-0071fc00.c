
allocator<char> * __thiscall
FUN_0071fc00(allocator<char> *param_1,allocator<char> *param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00858ab8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar2 = std::allocator<char>::allocator<char>(param_2);
  uVar2 = FUN_00417780(uVar2,param_3,uVar1);
  FUN_00725e10(uVar2,param_3);
  local_8 = 0;
  uVar2 = std::allocator<char>::allocator<char>(param_2);
  std::allocator<char>::allocator<char>(param_1);
  FUN_0071ff00(uVar2);
  ExceptionList = local_10;
  return param_1;
}

