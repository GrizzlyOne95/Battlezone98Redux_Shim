
void FUN_00444f20(int param_1)

{
  undefined4 *local_8;
  
  local_8 = DAT_0260d0f8;
  while( true ) {
    if (local_8 == (undefined4 *)0x0) {
      return;
    }
    if (local_8[2] == param_1) break;
    local_8 = (undefined4 *)*local_8;
  }
  std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>(param_1);
  FUN_008245a0(&DAT_0260d0f8,local_8);
  return;
}

