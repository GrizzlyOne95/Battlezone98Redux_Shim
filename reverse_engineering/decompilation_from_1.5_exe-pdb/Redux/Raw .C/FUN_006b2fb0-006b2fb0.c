
void __thiscall FUN_006b2fb0(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar1 = (undefined4 *)std::allocator<char>::allocator<char>((allocator<char> *)&local_18);
  *puVar1 = *param_1;
  puVar1[1] = param_1[1];
  puVar1[2] = param_1[2];
  puVar1[3] = param_1[3];
  *param_2 = local_18;
  param_2[1] = local_14;
  param_2[2] = local_10;
  param_2[3] = local_c;
  FUN_0083e885();
  return;
}

