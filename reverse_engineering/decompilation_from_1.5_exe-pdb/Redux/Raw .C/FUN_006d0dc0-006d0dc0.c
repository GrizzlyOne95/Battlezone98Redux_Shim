
allocator<char> * __fastcall FUN_006d0dc0(allocator<char> *param_1)

{
  std::allocator<char>::allocator<char>(param_1);
  *(undefined4 *)param_1 = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  return param_1;
}

