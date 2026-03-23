
bool FUN_006d0bd0(allocator<char> *param_1,allocator<char> *param_2)

{
  int *piVar1;
  int *piVar2;
  
  piVar1 = (int *)std::allocator<char>::allocator<char>(param_1);
  piVar2 = (int *)std::allocator<char>::allocator<char>(param_2);
  return *piVar1 == *piVar2;
}

