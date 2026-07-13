
int * FUN_006d9650(int *param_1,char param_2)

{
  char cVar1;
  uint _FileHandle;
  int *piVar2;
  __int64 _Var3;
  uint local_6c;
  int local_68;
  int local_64;
  int iStack_60;
  int local_5c;
  int local_58;
  int local_50;
  int local_4c;
  int local_48;
  basic_streambuf<char,struct_std::char_traits<char>_> *local_44;
  int local_40;
  int local_3c;
  int local_38;
  basic_streambuf<char,struct_std::char_traits<char>_> *local_34;
  int local_30;
  int local_2c;
  int local_28;
  basic_streambuf<char,struct_std::char_traits<char>_> *local_24;
  uint local_20;
  uint local_1c;
  char local_16;
  char local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00853758;
  local_10 = ExceptionList;
  _FileHandle = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = &stack0xffffff7c;
  ExceptionList = &local_10;
  local_1c = 0;
  FUN_004bb950(param_1);
  local_8 = 0;
  cVar1 = FUN_0041f990();
  if (cVar1 == '\0') {
    std::ios_base::width((ios_base *)((int)param_1 + *(int *)(*param_1 + 4)),0);
    std::basic_ios<char,struct_std::char_traits<char>_>::setstate
              ((basic_ios<char,struct_std::char_traits<char>_> *)
               ((int)param_1 + *(int *)(*param_1 + 4)),local_1c,false);
    local_8 = 0xffffffff;
    FUN_004bba20();
    ExceptionList = local_10;
    return param_1;
  }
  _Var3 = std::ios_base::width((ios_base *)((int)param_1 + *(int *)(*param_1 + 4)));
  local_68 = (int)((ulonglong)_Var3 >> 0x20);
  if ((local_68 < 1) && ((_Var3 < 0 || (local_6c = (uint)_Var3, local_6c < 2)))) {
    local_64 = 0;
    iStack_60 = 0;
  }
  else {
    _Var3 = std::ios_base::width((ios_base *)((int)param_1 + *(int *)(*param_1 + 4)));
    local_64 = (int)_Var3 + -1;
    iStack_60 = (int)((ulonglong)_Var3 >> 0x20) - (uint)((int)_Var3 == 0);
  }
  local_5c = local_64;
  local_58 = iStack_60;
  local_8 = CONCAT31(local_8._1_3_,1);
  local_20 = std::ios_base::flags((ios_base *)((int)param_1 + *(int *)(*param_1 + 4)));
  if ((local_20 & 0x1c0) != 0x40) {
    for (; ((local_1c == 0 && (-1 < local_58)) && ((0 < local_58 || (local_5c != 0))));
        local_5c = local_5c + -1) {
      local_15 = std::basic_ios<char,struct_std::char_traits<char>_>::fill
                           ((basic_ios<char,struct_std::char_traits<char>_> *)
                            ((int)param_1 + *(int *)(*param_1 + 4)));
      local_24 = std::basic_ios<char,struct_std::char_traits<char>_>::rdbuf
                           ((basic_ios<char,struct_std::char_traits<char>_> *)
                            ((int)param_1 + *(int *)(*param_1 + 4)));
      local_2c = std::basic_streambuf<char,struct_std::char_traits<char>_>::sputc(local_24,local_15)
      ;
      local_28 = local_2c;
      local_30 = eof(_FileHandle);
      cVar1 = eq_int_type(&local_30,&local_2c);
      if (cVar1 != '\0') {
        local_1c = local_1c | 4;
      }
      local_58 = local_58 - (uint)(local_5c == 0);
    }
  }
  if (local_1c == 0) {
    local_34 = std::basic_ios<char,struct_std::char_traits<char>_>::rdbuf
                         ((basic_ios<char,struct_std::char_traits<char>_> *)
                          ((int)param_1 + *(int *)(*param_1 + 4)));
    local_3c = std::basic_streambuf<char,struct_std::char_traits<char>_>::sputc(local_34,param_2);
    local_38 = local_3c;
    local_40 = eof(_FileHandle);
    cVar1 = eq_int_type(&local_40,&local_3c);
    if (cVar1 != '\0') {
      local_1c = local_1c | 4;
    }
  }
  for (; ((local_1c == 0 && (-1 < local_58)) && ((0 < local_58 || (local_5c != 0))));
      local_5c = local_5c + -1) {
    local_16 = std::basic_ios<char,struct_std::char_traits<char>_>::fill
                         ((basic_ios<char,struct_std::char_traits<char>_> *)
                          ((int)param_1 + *(int *)(*param_1 + 4)));
    local_44 = std::basic_ios<char,struct_std::char_traits<char>_>::rdbuf
                         ((basic_ios<char,struct_std::char_traits<char>_> *)
                          ((int)param_1 + *(int *)(*param_1 + 4)));
    local_4c = std::basic_streambuf<char,struct_std::char_traits<char>_>::sputc(local_44,local_16);
    local_48 = local_4c;
    local_50 = eof(_FileHandle);
    cVar1 = eq_int_type(&local_50,&local_4c);
    if (cVar1 != '\0') {
      local_1c = local_1c | 4;
    }
    local_58 = local_58 - (uint)(local_5c == 0);
  }
  piVar2 = (int *)FUN_006d98d0();
  return piVar2;
}

