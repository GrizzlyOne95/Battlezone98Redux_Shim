
void FUN_00574730(int *param_1)

{
  char cVar1;
  uint _FileHandle;
  char *pcVar2;
  __int64 _Var3;
  undefined4 uVar4;
  uint local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_50;
  int local_4c;
  int local_48;
  basic_streambuf<char,struct_std::char_traits<char>_> *local_44;
  basic_streambuf<char,struct_std::char_traits<char>_> *local_40;
  int local_3c;
  int local_38;
  int local_34;
  basic_streambuf<char,struct_std::char_traits<char>_> *local_30;
  uint local_2c;
  int local_28;
  uint local_24;
  int local_20;
  uint local_1c;
  char local_16;
  char local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b7d8;
  local_10 = ExceptionList;
  _FileHandle = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = &stack0xffffff7c;
  ExceptionList = &local_10;
  local_1c = 0;
  local_24 = FUN_004170c0();
  _Var3 = std::ios_base::width((ios_base *)((int)param_1 + *(int *)(*param_1 + 4)));
  local_58 = (int)((ulonglong)_Var3 >> 0x20);
  if ((_Var3 < 0) ||
     (((local_58 < 1 && (local_5c = (int)_Var3, local_5c == 0)) ||
      (_Var3 = std::ios_base::width((ios_base *)((int)param_1 + *(int *)(*param_1 + 4))),
      (uint)_Var3 <= local_24)))) {
    local_28 = 0;
  }
  else {
    _Var3 = std::ios_base::width((ios_base *)((int)param_1 + *(int *)(*param_1 + 4)));
    local_28 = (int)_Var3 - local_24;
  }
  local_20 = local_28;
  FUN_004bb950(param_1);
  local_8 = 0;
  cVar1 = FUN_0041f990();
  if (cVar1 == '\0') {
    local_1c = local_1c | 4;
    FUN_005749c9();
    return;
  }
  local_8 = CONCAT31(local_8._1_3_,1);
  local_2c = std::ios_base::flags((ios_base *)((int)param_1 + *(int *)(*param_1 + 4)));
  if ((local_2c & 0x1c0) != 0x40) {
    for (; local_20 != 0; local_20 = local_20 + -1) {
      local_15 = std::basic_ios<char,struct_std::char_traits<char>_>::fill
                           ((basic_ios<char,struct_std::char_traits<char>_> *)
                            ((int)param_1 + *(int *)(*param_1 + 4)));
      local_30 = std::basic_ios<char,struct_std::char_traits<char>_>::rdbuf
                           ((basic_ios<char,struct_std::char_traits<char>_> *)
                            ((int)param_1 + *(int *)(*param_1 + 4)));
      local_38 = std::basic_streambuf<char,struct_std::char_traits<char>_>::sputc(local_30,local_15)
      ;
      local_34 = local_38;
      local_3c = eof(_FileHandle);
      cVar1 = eq_int_type(&local_3c,&local_38);
      if (cVar1 != '\0') {
        local_1c = local_1c | 4;
        break;
      }
    }
  }
  if (local_1c == 0) {
    local_40 = std::basic_ios<char,struct_std::char_traits<char>_>::rdbuf
                         ((basic_ios<char,struct_std::char_traits<char>_> *)
                          ((int)param_1 + *(int *)(*param_1 + 4)));
    uVar4 = 0;
    pcVar2 = (char *)FUN_0041f870(local_24);
    _Var3 = std::basic_streambuf<char,struct_std::char_traits<char>_>::sputn
                      (local_40,pcVar2,CONCAT44(_FileHandle,uVar4));
    local_64 = (uint)_Var3;
    if ((local_64 != local_24) || (local_60 = (int)((ulonglong)_Var3 >> 0x20), local_60 != 0)) {
      local_1c = local_1c | 4;
      goto LAB_00574983;
    }
  }
  for (; local_20 != 0; local_20 = local_20 + -1) {
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
      break;
    }
  }
LAB_00574983:
  std::ios_base::width((ios_base *)((int)param_1 + *(int *)(*param_1 + 4)),0);
  FUN_005749b9();
  return;
}

