
void FUN_006b5810(char param_1,
                 basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                 *param_2,undefined4 param_3,
                 basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                 *param_4)

{
  char cVar1;
  undefined2 uVar2;
  uint uVar3;
  undefined1 local_70 [8];
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  uint local_58;
  undefined **local_54;
  undefined4 local_50;
  int local_4c;
  uint local_48;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850a97;
  local_10 = ExceptionList;
  uVar3 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_48 = 0;
  if (param_1 == '\0') {
    local_54 = (undefined **)&DAT_00896cb4;
  }
  else {
    local_54 = &PTR_LAB_00896ca8;
  }
  local_14 = uVar3;
  basic_string<>(local_54);
  local_8 = 0;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (local_4c + 0x18),param_2);
  local_8._0_1_ = 1;
  cVar1 = FUN_0041f890(uVar3);
  if (cVar1 == '\0') {
    local_64 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
               basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         (local_2c,param_4);
    local_48 = local_48 | 2;
    local_50 = local_64;
  }
  else {
    local_68 = basic_string<>(&DAT_008922f8);
    local_8._0_1_ = 2;
    local_48 = local_48 | 1;
    local_5c = local_68;
    local_50 = local_68;
  }
  local_60 = local_50;
  basic_string<>(local_50);
  local_8 = 3;
  if ((local_48 & 2) != 0) {
    local_48 = local_48 & 0xfffffffd;
    ~basic_string<>();
  }
  local_8 = CONCAT31(local_8._1_3_,4);
  if ((local_48 & 1) != 0) {
    local_48 = local_48 & 0xfffffffe;
    ~basic_string<>();
  }
  *(char *)(local_4c + 0x4a) = param_1;
  FUN_006ab750();
  uVar2 = FUN_006b61b0(param_3,local_70);
  *(undefined2 *)(local_4c + 0x48) = uVar2;
  cVar1 = FUN_006ab7d0();
  local_58 = (uint)(cVar1 == '\0');
  *(bool *)(local_4c + 0x4b) = cVar1 == '\0';
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

