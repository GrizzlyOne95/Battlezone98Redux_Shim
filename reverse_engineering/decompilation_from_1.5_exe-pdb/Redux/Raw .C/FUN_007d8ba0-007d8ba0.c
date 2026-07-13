
int __thiscall
FUN_007d8ba0(int param_1,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 local_1c [8];
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0086302b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = param_1;
  uVar2 = FUN_007d9560(param_1);
  uVar2 = FUN_007d9c30(local_1c,uVar2,uVar1);
  _Callable_base<>(uVar2);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (local_14 + 4),param_2);
  local_8 = 0;
  FUN_00430590();
  ExceptionList = local_10;
  return local_14;
}

