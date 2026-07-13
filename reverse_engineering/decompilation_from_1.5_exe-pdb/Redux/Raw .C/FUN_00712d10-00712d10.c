
undefined4 * __thiscall FUN_00712d10(undefined4 *param_1,int param_2)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00857ab8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00712640(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = std::
             _Func_impl<struct_std::_Callable_obj<bool_(__cdecl*)(class_std::weak_ptr<void>,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_const&),0>,class_std::allocator<class_std::_Func_class<bool,class_std::weak_ptr<void>,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>_>,bool,class_std::weak_ptr<void>,class_std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_>
             ::vftable;
  uVar1 = FUN_00417780(param_2 + 4);
  FUN_0071b2b0(uVar1);
  allocator<>(param_2 + 8);
  ExceptionList = local_10;
  return param_1;
}

