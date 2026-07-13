
int FUN_007d8b50(undefined4 param_1,
                basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                *param_2)

{
  undefined4 uVar1;
  undefined1 local_10 [8];
  int local_8;
  
  uVar1 = FUN_007d9560(param_1);
  uVar1 = FUN_007d9c30(local_10,uVar1);
  _Callable_base<>(uVar1);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (local_8 + 8),param_2);
  return local_8;
}

