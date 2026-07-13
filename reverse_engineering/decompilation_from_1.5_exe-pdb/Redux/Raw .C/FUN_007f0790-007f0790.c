
void FUN_007f0790(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar4;
  undefined1 local_40 [19];
  undefined1 local_2d;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844a78;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  iVar2 = FUN_007df2f0(local_14);
  if (iVar2 != 0) {
    uVar3 = FUN_00417780(param_4);
    pbVar4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             FUN_00423b10(uVar3);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,pbVar4);
    local_8 = 0;
    FUN_007ef2f0(local_2c);
    cVar1 = FUN_007df230(param_1,local_40,param_3);
    if (cVar1 == '\0') {
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
    else {
      operator==<>(param_1,param_3);
      local_2d = 1;
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

