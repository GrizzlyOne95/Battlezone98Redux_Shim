
void __thiscall FUN_0076bd70(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  undefined1 local_a8 [148];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085d89b;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *(undefined4 *)(param_1 + 0x8c) = 0;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x90),"**INVALID**");
  uVar1 = FUN_0076f2b0(param_2);
  FUN_00769f40(uVar1);
  local_8 = 0;
  uVar1 = FUN_0076f2b0(param_2 + -1);
  FUN_0076f2b0(param_2);
  FUN_0076be70(uVar1);
  puVar2 = local_a8;
  FUN_0076f2b0(param_2 + -1);
  FUN_0076be70(puVar2);
  local_8 = 0xffffffff;
  FUN_00769ff0();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

