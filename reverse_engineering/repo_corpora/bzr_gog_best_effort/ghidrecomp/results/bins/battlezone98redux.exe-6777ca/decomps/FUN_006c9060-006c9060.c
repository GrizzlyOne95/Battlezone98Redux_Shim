
allocator<char> * __thiscall
FUN_006c9060(allocator<char> *param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849b78;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  std::allocator<char>::allocator<char>(param_1);
  local_8 = 0;
  *(undefined4 *)param_1 = param_2;
  *(undefined4 *)(param_1 + 4) = param_3;
  uVar2 = FUN_006cd800(uVar1);
  *(undefined4 *)(param_1 + 8) = uVar2;
  FUN_006cd7e0(param_1);
  ExceptionList = local_10;
  return param_1;
}

