
int __thiscall
FUN_007fbf60(int param_1,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 local_28 [8];
  undefined4 local_20;
  undefined4 local_1c;
  void *local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008631a7;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = param_1;
  uVar2 = FUN_007d9560(param_1);
  uVar2 = FUN_007d9c30(local_28,uVar2,uVar1);
  _Callable_base<>(uVar2);
  FUN_00447eb0(local_14);
  FUN_00447eb0(local_14);
  local_18 = operator_new(4);
  local_8 = 0;
  if (local_18 == (void *)0x0) {
    local_1c = 0;
  }
  else {
    local_1c = FUN_00423890();
  }
  local_20 = local_1c;
  local_8 = 0xffffffff;
  FUN_007fc580(local_1c);
  local_8 = 1;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (local_14 + 0x14),param_2);
  ExceptionList = local_10;
  return local_14;
}

