
undefined4
FUN_0080f620(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined1 *param_5)

{
  undefined4 *puVar1;
  undefined1 local_30 [20];
  undefined4 *local_1c [5];
  undefined4 local_8;
  
  std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>(*param_5);
  local_8 = *param_1;
  FUN_007e9db0(&local_8,param_2,param_3,param_4);
  puVar1 = (undefined4 *)FUN_0080bfe0(local_30,local_1c,param_5);
  FUN_008105f0(*puVar1,puVar1[1],puVar1[2],puVar1[3],puVar1[4]);
  *param_1 = *local_1c[0];
  return 1;
}

