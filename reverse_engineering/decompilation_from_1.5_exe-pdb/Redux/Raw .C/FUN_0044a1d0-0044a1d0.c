
bad_alloc * __thiscall FUN_0044a1d0(bad_alloc *param_1,bad_alloc *param_2)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00846128;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  std::bad_alloc::bad_alloc(param_1,param_2);
  local_8 = 0;
  *(undefined ***)param_1 = boost::system::system_error::vftable;
  uVar1 = *(undefined4 *)(param_2 + 0x10);
  *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(param_2 + 0xc);
  *(undefined4 *)(param_1 + 0x10) = uVar1;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x14),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_2 + 0x14));
  ExceptionList = local_10;
  return param_1;
}

