
undefined4 FUN_006f1870(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int local_c4 [38];
  undefined1 local_2c [16];
  locale local_1c [4];
  uint local_18;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085508b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_18 = 0;
  FUN_006ca050(2,1);
  local_8 = 0;
  std::locale::classic();
  std::basic_ios<char,struct_std::char_traits<char>_>::imbue
            ((basic_ios<char,struct_std::char_traits<char>_> *)
             ((int)local_c4 + *(int *)(local_c4[0] + 4)),local_1c);
  FUN_00417b50(uVar1);
  uVar2 = FUN_006dc270(&local_11,0x30);
  uVar3 = std::setw(CONCAT44(param_4,local_2c));
  uVar2 = FUN_006db8a0(local_c4,uVar3,uVar2);
  FUN_006dc290(uVar2);
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
            ((basic_ostream<char,struct_std::char_traits<char>_> *)local_c4,
             CONCAT44(param_3,param_2));
  GetPolicy(param_1);
  local_18 = local_18 | 1;
  local_8 = 0xffffffff;
  FUN_006b3a50();
  ExceptionList = local_10;
  return param_1;
}

