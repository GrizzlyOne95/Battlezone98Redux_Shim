
void FUN_0056ad10(char *param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 extraout_var;
  undefined4 uVar3;
  char *local_38;
  char *local_34;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844a78;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &DAT_009c8e28,"");
  uVar3 = extraout_var;
  FUN_005d48c0(uVar2,extraout_var);
  cVar1 = operator!=<>(&DAT_009c8e28,&DAT_008a1ad8);
  if (cVar1 != '\0') {
    basic_string<>(&DAT_02cf3000);
    local_8 = 0;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_2c,"\\");
    FUN_00449810(&DAT_009c8e28);
    local_38 = (char *)FUN_0041f870();
    local_34 = param_1;
    do {
      cVar1 = *local_38;
      *local_34 = cVar1;
      local_38 = local_38 + 1;
      local_34 = local_34 + 1;
    } while (cVar1 != '\0');
    local_8 = 0xffffffff;
    ~basic_string<>(uVar2,uVar3,param_1);
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

