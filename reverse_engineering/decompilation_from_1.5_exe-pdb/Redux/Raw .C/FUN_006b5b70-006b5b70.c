
void __thiscall
FUN_006b5b70(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_1,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_3,
            undefined4 param_4,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_5)

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
  undefined4 local_54;
  undefined4 local_50;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_4c;
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
  local_4c = param_1;
  local_14 = uVar3;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(param_1,param_2);
  local_8 = 0;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (local_4c + 0x18,param_3);
  local_8._0_1_ = 1;
  cVar1 = FUN_0041f890(uVar3);
  if (cVar1 == '\0') {
    local_64 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
               basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         (local_2c,param_5);
    local_48 = local_48 | 2;
    local_54 = local_64;
  }
  else {
    local_68 = basic_string<>(&DAT_008922f8);
    local_8._0_1_ = 2;
    local_48 = local_48 | 1;
    local_5c = local_68;
    local_54 = local_68;
  }
  local_60 = local_54;
  basic_string<>(local_54);
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
  cVar1 = FUN_00427270(param_2,&PTR_LAB_00896ca8);
  if ((cVar1 == '\0') && (cVar1 = FUN_00427270(param_2,"https"), cVar1 == '\0')) {
    local_50 = 0;
  }
  else {
    local_50 = 1;
  }
  local_4c[0x4a] = local_50._0_1_;
  FUN_006ab750();
  uVar2 = FUN_006b61b0(param_4,local_70);
  *(undefined2 *)(local_4c + 0x48) = uVar2;
  cVar1 = FUN_006ab7d0();
  local_58 = (uint)(cVar1 == '\0');
  local_4c[0x4b] =
       (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>)(cVar1 == '\0')
  ;
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

