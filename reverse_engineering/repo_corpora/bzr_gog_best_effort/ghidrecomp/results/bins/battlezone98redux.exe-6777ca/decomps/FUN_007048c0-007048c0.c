
int __thiscall FUN_007048c0(int param_1,int param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00856cf8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00704b40(param_2);
  local_8 = 0;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x48),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_2 + 0x48));
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_2 + 0x60);
  std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
            ((shared_ptr<class___ExceptionPtr> *)(param_1 + 100),
             (shared_ptr<class___ExceptionPtr> *)(param_2 + 100));
  *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(param_2 + 0x6c);
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_2 + 0x70);
  ExceptionList = local_10;
  return param_1;
}

