
void __thiscall
FUN_006b56a0(int param_1,char param_2,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_3,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_4)

{
  char cVar1;
  uint uVar2;
  bool bVar3;
  undefined4 local_58;
  undefined **local_54;
  undefined2 local_4e;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850a2c;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if (param_2 == '\0') {
    local_54 = (undefined **)&DAT_00896cb4;
  }
  else {
    local_54 = &PTR_LAB_00896ca8;
  }
  local_14 = uVar2;
  basic_string<>(local_54);
  local_8 = 0;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x18),param_3);
  local_8._0_1_ = 1;
  cVar1 = FUN_0041f890(uVar2);
  bVar3 = cVar1 == '\0';
  if (bVar3) {
    local_58 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
               basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         (local_2c,param_4);
  }
  else {
    local_58 = basic_string<>(&DAT_008922f8);
    local_8._0_1_ = 2;
  }
  basic_string<>(local_58);
  if (bVar3) {
    ~basic_string<>();
  }
  local_8 = 1;
  if (!bVar3) {
    ~basic_string<>();
  }
  if (param_2 == '\0') {
    local_4e = 0x50;
  }
  else {
    local_4e = 0x1bb;
  }
  *(undefined2 *)(param_1 + 0x48) = local_4e;
  *(char *)(param_1 + 0x4a) = param_2;
  *(undefined1 *)(param_1 + 0x4b) = 1;
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

