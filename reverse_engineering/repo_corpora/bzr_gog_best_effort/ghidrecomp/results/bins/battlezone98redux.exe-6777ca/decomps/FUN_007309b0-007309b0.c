
allocator<char> * __thiscall FUN_007309b0(allocator<char> *param_1,allocator<char> *param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  allocator<char> *paVar5;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00859cf8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  paVar5 = param_2;
  uVar1 = FUN_006d0a70(&local_11);
  FUN_00730c50(uVar1,paVar5);
  local_8 = 0;
  uVar1 = std::allocator<char>::allocator<char>(param_1);
  puVar2 = (undefined4 *)FUN_00447eb0(uVar1);
  uVar1 = *puVar2;
  puVar2 = (undefined4 *)FUN_00447eb0(param_1);
  uVar4 = *puVar2;
  uVar3 = std::allocator<char>::allocator<char>(param_2);
  std::allocator<char>::allocator<char>(param_1);
  FUN_00732750(uVar3,uVar4,uVar1);
  ExceptionList = local_10;
  return param_1;
}

