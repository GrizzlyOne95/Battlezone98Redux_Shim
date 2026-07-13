
void FUN_004bc590(int *param_1,char *param_2)

{
  char cVar1;
  uint _FileHandle;
  uint uVar2;
  bool bVar3;
  __int64 _Var4;
  uint local_78;
  int local_74;
  uint local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int iStack_5c;
  int local_50;
  int local_4c;
  int local_44;
  int local_40;
  int local_3c;
  basic_streambuf<char,struct_std::char_traits<char>_> *local_38;
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
  puStack_c = &LAB_00849bc8;
  local_10 = ExceptionList;
  _FileHandle = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = &stack0xffffff70;
  ExceptionList = &local_10;
  local_1c = 0;
  uVar2 = FUN_00416290(param_2);
  _Var4 = std::ios_base::width((ios_base *)((int)param_1 + *(int *)(*param_1 + 4)));
  local_64 = (int)((ulonglong)_Var4 >> 0x20);
  if ((-1 < _Var4) && ((0 < local_64 || (local_68 = (int)_Var4, local_68 != 0)))) {
    _Var4 = std::ios_base::width((ios_base *)((int)param_1 + *(int *)(*param_1 + 4)));
    local_6c = (int)((ulonglong)_Var4 >> 0x20);
    if ((-1 < _Var4) && ((0 < local_6c || (local_70 = (uint)_Var4, uVar2 < local_70)))) {
      _Var4 = std::ios_base::width((ios_base *)((int)param_1 + *(int *)(*param_1 + 4)));
      local_60 = (uint)_Var4 - uVar2;
      iStack_5c = (int)((ulonglong)_Var4 >> 0x20) - (uint)((uint)_Var4 < uVar2);
      goto LAB_004bc64d;
    }
  }
  local_60 = 0;
  iStack_5c = 0;
LAB_004bc64d:
  local_50 = local_60;
  local_4c = iStack_5c;
  FUN_004bb950(param_1);
  local_8 = 0;
  cVar1 = FUN_0041f990();
  if (cVar1 == '\0') {
    local_1c = local_1c | 4;
    FUN_004bc878();
    return;
  }
  local_8 = CONCAT31(local_8._1_3_,1);
  local_20 = std::ios_base::flags((ios_base *)((int)param_1 + *(int *)(*param_1 + 4)));
  if ((local_20 & 0x1c0) != 0x40) {
    while( true ) {
      if ((local_4c < 0) || ((local_4c < 1 && (local_50 == 0)))) goto LAB_004bc748;
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
      if (cVar1 != '\0') break;
      bVar3 = local_50 == 0;
      local_50 = local_50 + -1;
      local_4c = local_4c - (uint)bVar3;
    }
    local_1c = local_1c | 4;
  }
LAB_004bc748:
  if (local_1c == 0) {
    local_34 = std::basic_ios<char,struct_std::char_traits<char>_>::rdbuf
                         ((basic_ios<char,struct_std::char_traits<char>_> *)
                          ((int)param_1 + *(int *)(*param_1 + 4)));
    _Var4 = std::basic_streambuf<char,struct_std::char_traits<char>_>::sputn
                      (local_34,param_2,(ulonglong)_FileHandle << 0x20);
    local_78 = (uint)_Var4;
    if ((local_78 != uVar2) || (local_74 = (int)((ulonglong)_Var4 >> 0x20), local_74 != 0)) {
      local_1c = local_1c | 4;
    }
  }
  if (local_1c == 0) {
    while( true ) {
      if ((local_4c < 0) || ((local_4c < 1 && (local_50 == 0)))) goto LAB_004bc832;
      local_16 = std::basic_ios<char,struct_std::char_traits<char>_>::fill
                           ((basic_ios<char,struct_std::char_traits<char>_> *)
                            ((int)param_1 + *(int *)(*param_1 + 4)));
      local_38 = std::basic_ios<char,struct_std::char_traits<char>_>::rdbuf
                           ((basic_ios<char,struct_std::char_traits<char>_> *)
                            ((int)param_1 + *(int *)(*param_1 + 4)));
      local_40 = std::basic_streambuf<char,struct_std::char_traits<char>_>::sputc(local_38,local_16)
      ;
      local_3c = local_40;
      local_44 = eof(_FileHandle);
      cVar1 = eq_int_type(&local_44,&local_40);
      if (cVar1 != '\0') break;
      bVar3 = local_50 == 0;
      local_50 = local_50 + -1;
      local_4c = local_4c - (uint)bVar3;
    }
    local_1c = local_1c | 4;
  }
LAB_004bc832:
  std::ios_base::width((ios_base *)((int)param_1 + *(int *)(*param_1 + 4)),0);
  FUN_004bc868();
  return;
}

