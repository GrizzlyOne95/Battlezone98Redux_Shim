
void __thiscall
FUN_0080e1c0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  
  uVar1 = __Cnd_init_in_situ(param_2,param_1);
  FUN_0080f7f0(uVar1);
  puVar2 = (undefined1 *)FUN_0066f210();
  uVar1 = FUN_0080e040(&stack0xfffffffa,param_2,param_3,param_4,*puVar2);
  std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>(uVar1);
  return;
}

