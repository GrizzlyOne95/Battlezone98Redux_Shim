
int __fastcall FUN_006e1d10(allocator<char> *param_1)

{
  int *piVar1;
  
  piVar1 = (int *)std::allocator<char>::allocator<char>(param_1);
  return *(int *)(param_1 + 4) * 0x20 + *piVar1;
}

