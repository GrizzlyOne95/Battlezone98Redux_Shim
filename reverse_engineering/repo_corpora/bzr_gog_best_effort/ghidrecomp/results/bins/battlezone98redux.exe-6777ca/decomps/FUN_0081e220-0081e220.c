
void FUN_0081e220(undefined4 param_1,char param_2)

{
  uint uVar1;
  basic_streambuf<char,struct_std::char_traits<char>_> *this;
  char *pcVar2;
  undefined4 uVar3;
  locale local_8c [4];
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_68;
  locale local_64 [4];
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  void *local_44;
  void *local_40;
  undefined4 local_3c;
  undefined4 local_38;
  uint local_34;
  int *local_30;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00865059;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_34 = 0;
  local_14 = uVar1;
  FUN_0066af10();
  local_8 = 0;
  uVar3 = 0;
  pcVar2 = (char *)0x0;
  this = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
  std::basic_streambuf<char,struct_std::char_traits<char>_>::pubsetbuf
            (this,pcVar2,CONCAT44(uVar1,uVar3));
  FUN_00662ea0();
  local_8._0_1_ = 1;
  FUN_006668f0();
  FUN_004cfa00();
  FUN_0081e0a0();
  FUN_0081e920();
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
            ((basic_ostream<char,struct_std::char_traits<char>_> *)(local_30 + 4),FUN_0081e080);
  if (param_2 == '\0') {
    local_40 = operator_new(0x114);
    local_8._0_1_ = 9;
    if (local_40 == (void *)0x0) {
      local_3c = 0;
    }
    else {
      local_78 = FUN_006ccb70();
      local_8._0_1_ = 10;
      local_48 = FUN_006ccef0();
      local_8 = CONCAT31(local_8._1_3_,0xb);
      local_34 = local_34 | 2;
      FUN_006cce50(1,&DAT_008961b8,&DAT_00896190,&DAT_00896290,&DAT_008961bc);
      local_8 = 0xc;
      local_3c = FUN_006cc7d0("%Y-%m-%d %H:%M:%S ");
    }
    local_8 = 0xd;
    local_88 = std::ios_base::getloc((ios_base *)((int)local_30 + *(int *)(*local_30 + 4)));
    local_8 = 0xe;
    local_4c = local_88;
    local_5c = FUN_006db9f0();
    local_8._0_1_ = 0xf;
    local_54 = local_5c;
    std::basic_ios<char,struct_std::char_traits<char>_>::imbue
              ((basic_ios<char,struct_std::char_traits<char>_> *)
               ((int)local_30 + *(int *)(*local_30 + 4)),local_64);
    FUN_00417b50();
    local_8._0_1_ = 0xe;
    FUN_00417b50();
    local_8 = CONCAT31(local_8._1_3_,0xd);
    FUN_00417b50();
    local_8 = 1;
    if ((local_34 & 2) != 0) {
      local_34 = local_34 & 0xfffffffd;
      FUN_006c3560();
    }
  }
  else {
    local_44 = operator_new(0x114);
    local_8._0_1_ = 2;
    if (local_44 == (void *)0x0) {
      local_38 = 0;
    }
    else {
      FUN_006ccb70();
      local_8._0_1_ = 3;
      local_80 = FUN_006ccef0();
      local_8 = CONCAT31(local_8._1_3_,4);
      local_34 = local_34 | 1;
      local_50 = local_80;
      FUN_006cce50(1,&DAT_008961b8,&DAT_00896190,&DAT_00896290,&DAT_008961bc);
      local_8 = 5;
      local_38 = FUN_006cc7d0("%Y-%m-%d %H:%M:%S.%f ");
    }
    local_7c = local_38;
    local_8 = 6;
    local_60 = std::ios_base::getloc((ios_base *)((int)local_30 + *(int *)(*local_30 + 4)));
    local_8 = 7;
    local_58 = local_60;
    local_84 = FUN_006db9f0();
    local_8._0_1_ = 8;
    local_68 = local_84;
    std::basic_ios<char,struct_std::char_traits<char>_>::imbue
              ((basic_ios<char,struct_std::char_traits<char>_> *)
               ((int)local_30 + *(int *)(*local_30 + 4)),local_8c);
    FUN_00417b50();
    local_8._0_1_ = 7;
    FUN_00417b50();
    local_8 = CONCAT31(local_8._1_3_,6);
    FUN_00417b50();
    local_8 = 1;
    if ((local_34 & 1) != 0) {
      local_34 = local_34 & 0xfffffffe;
      FUN_006c3560();
    }
  }
  local_8 = local_8 & 0xffffff00;
  FUN_004180b0();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

