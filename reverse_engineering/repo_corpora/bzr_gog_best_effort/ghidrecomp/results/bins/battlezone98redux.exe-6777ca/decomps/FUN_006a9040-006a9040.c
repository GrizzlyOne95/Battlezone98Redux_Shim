
void FUN_006a9040(int param_1,int param_2,undefined4 param_3)

{
  if (param_1 == param_2) {
    param_3 = 4;
  }
  *(undefined4 *)(&DAT_02ce99e4 + param_2 * 4 + param_1 * 0x1e0) = param_3;
  std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>(param_1);
  std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>(param_2);
  std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>(param_1);
  std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>(param_2);
  return;
}

