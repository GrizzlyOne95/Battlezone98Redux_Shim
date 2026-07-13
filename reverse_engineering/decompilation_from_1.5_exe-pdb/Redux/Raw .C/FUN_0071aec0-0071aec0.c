
undefined4 FUN_0071aec0(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 local_14;
  undefined1 *local_10;
  allocator<char> *local_c;
  
  uStack_18 = param_2;
  uStack_1c = 0x71aed2;
  uStack_18 = FUN_00417780();
  uStack_1c = param_1;
  uStack_20 = 0x71aedf;
  uVar1 = FUN_00417780();
  local_10 = (undefined1 *)&uStack_20;
  local_14 = shared_ptr<>(uVar1);
  puVar2 = (undefined4 *)std::allocator<char>::allocator<char>(local_c);
  uVar1 = (*(code *)*puVar2)();
  return uVar1;
}

