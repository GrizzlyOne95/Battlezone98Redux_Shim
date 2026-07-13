
int __thiscall FUN_007ef2f0(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  allocator<char> local_5;
  
  uVar1 = std::allocator<char>::allocator<char>(&local_5);
  FUN_007dc230(param_2,uVar1);
  std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 8));
  return param_1;
}

