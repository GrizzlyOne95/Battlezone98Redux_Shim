
void FUN_0073bdb0(void)

{
  locale *plVar1;
  undefined4 uVar2;
  int local_10c [4];
  undefined1 auStack_fc [160];
  undefined1 local_5c [8];
  locale local_54 [4];
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_44;
  void *local_40;
  undefined4 local_3c;
  uint local_38;
  undefined1 *local_34;
  undefined4 local_30;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085a93f;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_38 = 0;
  local_8 = 0;
  FUN_00574400(3,1);
  local_8._0_1_ = 1;
  local_40 = operator_new(0x114);
  local_8._0_1_ = 2;
  if (local_40 == (void *)0x0) {
    local_3c = 0;
  }
  else {
    local_3c = FUN_006e1d70(0);
  }
  local_50 = local_3c;
  local_8._0_1_ = 1;
  local_30 = local_3c;
  FUN_007480d0("%H:%M");
  uVar2 = local_30;
  plVar1 = std::locale::classic();
  local_4c = FUN_006db9f0(plVar1,uVar2);
  local_8._0_1_ = 3;
  local_44 = local_4c;
  std::basic_ios<char,struct_std::char_traits<char>_>::imbue
            ((basic_ios<char,struct_std::char_traits<char>_> *)
             ((int)local_10c + *(int *)(local_10c[0] + 4)),local_54);
  FUN_00417b50();
  local_8._0_1_ = 1;
  FUN_00417b50();
  if (&stack0x00000000 == (undefined1 *)0x10c) {
    local_34 = (undefined1 *)0x0;
  }
  else {
    local_34 = auStack_fc;
  }
  uVar2 = FUN_006ccf80(local_5c);
  FUN_006dba70(local_34,uVar2);
  GetPolicy(local_2c);
  local_8._0_1_ = 4;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c," ");
  FUN_00449810(&stack0x00000008);
  basic_string<>(local_2c);
  local_38 = local_38 | 1;
  local_8._0_1_ = 1;
  ~basic_string<>();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00417f10();
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

