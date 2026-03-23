
void FUN_007efbf0(allocator<char> *param_1,byte *param_2)

{
  undefined1 *puVar1;
  uint uVar2;
  undefined4 extraout_var;
  
  uVar2 = (uint)*param_2;
  puVar1 = (undefined1 *)std::allocator<char>::allocator<char>((allocator<char> *)&stack0xfffffffa);
  FUN_007eab60(*puVar1,uVar2,extraout_var);
  puVar1 = &stack0xfffffffb;
  std::allocator<char>::allocator<char>(param_1);
  FUN_007f0750(puVar1);
  FUN_007efea0();
  FUN_007eba50(param_1);
  return;
}

