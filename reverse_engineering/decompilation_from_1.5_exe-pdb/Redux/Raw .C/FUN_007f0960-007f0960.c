
undefined4 FUN_007f0960(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  
  for (; param_2 != param_3; param_2 = param_2 + 2) {
    iVar1 = param_2;
    std::allocator<char>::allocator<char>((allocator<char> *)&stack0x00000010);
    FUN_007f1430(iVar1);
    FUN_007efea0();
  }
  FUN_007ee650(&stack0x00000010);
  return param_1;
}

