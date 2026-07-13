
undefined4 FUN_006cc200(allocator<char> *param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 local_c;
  undefined4 local_8;
  
  local_c = FUN_006d0c10();
  puVar2 = &local_c;
  uVar1 = std::allocator<char>::allocator<char>(param_1);
  FUN_006d0c30(uVar1,puVar2);
  return local_8;
}

