
undefined4 * __thiscall
FUN_006b2f30(undefined4 *param_1,allocator<char> *param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  
  param_1[4] = param_3;
  puVar1 = (undefined4 *)std::allocator<char>::allocator<char>(param_2);
  *param_1 = *puVar1;
  param_1[1] = puVar1[1];
  param_1[2] = puVar1[2];
  param_1[3] = puVar1[3];
  return param_1;
}

