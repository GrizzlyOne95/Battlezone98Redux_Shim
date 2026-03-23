
allocator<char> * __thiscall FUN_007305f0(allocator<char> *param_1,allocator<char> *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00859cc8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  uVar1 = FUN_00416410(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  uVar2 = std::allocator<char>::allocator<char>(param_2);
  uVar2 = FUN_00730ba0(uVar2,uVar1);
  FUN_007325e0(DAT_0260b03d,uVar2,uVar1);
  local_8 = 0;
  uVar1 = FUN_006d0da0();
  uVar1 = FUN_00416410(uVar1);
  uVar1 = FUN_006d0da0(uVar1);
  uVar2 = std::allocator<char>::allocator<char>(param_1);
  FUN_00732660(uVar2,uVar1);
  ExceptionList = local_10;
  return param_1;
}

