
void FUN_0079b880(char *param_1)

{
  int iVar1;
  undefined4 uStack_c4;
  char *pcStack_c0;
  undefined4 uStack_bc;
  undefined *puStack_b8;
  char *pcStack_b4;
  char *pcStack_b0;
  uint uStack_ac;
  undefined1 *local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined *local_6c;
  uint local_68;
  undefined4 local_64;
  undefined1 local_5c [24];
  undefined1 local_44 [48];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085f7fb;
  local_10 = ExceptionList;
  uStack_ac = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  pcStack_b0 = (char *)0x79b8c3;
  local_14 = uStack_ac;
  iVar1 = FUN_0056f900();
  if (iVar1 != 0) {
    pcStack_b0 = (char *)0x79b8d9;
    iVar1 = FUN_007a4220();
    if (iVar1 != 0) {
      local_68 = (uint)(*param_1 == '\0');
      *param_1 = *param_1 == '\0';
      pcStack_b0 = (char *)0x0;
      pcStack_b4 = (char *)0x0;
      puStack_b8 = (undefined *)0x0;
      uStack_bc = 0x79b914;
      FUN_00426b10();
      local_8._0_1_ = 1;
      pcStack_b0 = (char *)0x0;
      pcStack_b4 = &DAT_02cf2000;
      puStack_b8 = (undefined *)0x79b927;
      FUN_00426a60();
      local_8._0_1_ = 2;
      pcStack_b0 = "multi.ini";
      pcStack_b4 = (char *)0x79b938;
      FUN_00426af0();
      pcStack_b0 = local_5c;
      pcStack_b4 = (char *)0x79b944;
      local_78 = FUN_00417fd0();
      local_8._0_1_ = 3;
      pcStack_b0 = (char *)0x79b959;
      local_74 = local_78;
      pcStack_b0 = (char *)FUN_0041f870();
      pcStack_b4 = (char *)0x79b965;
      FUN_00426c30();
      local_8._0_1_ = 2;
      pcStack_b0 = (char *)0x79b971;
      ~basic_string<>();
      if (*param_1 == '\0') {
        local_6c = &DAT_00873c74;
      }
      else {
        local_6c = &DAT_00873ef0;
      }
      pcStack_b0 = (char *)0x1;
      pcStack_b4 = (char *)0x0;
      puStack_b8 = local_6c;
      uStack_bc = 0x79b99b;
      uStack_bc = FUN_0041f870();
      pcStack_c0 = "multi";
      uStack_c4 = 0x79b9ac;
      FUN_00421f90();
      pcStack_b0 = local_44;
      pcStack_b4 = (char *)0x79b9b8;
      local_7c = FUN_00417fd0();
      local_8._0_1_ = 4;
      pcStack_b0 = (char *)0x1;
      pcStack_b4 = (char *)0x79b9cf;
      local_70 = local_7c;
      pcStack_b4 = (char *)FUN_0041f870();
      puStack_b8 = (undefined *)0x79b9db;
      FUN_00426c90();
      local_8 = CONCAT31(local_8._1_3_,2);
      pcStack_b0 = (char *)0x79b9e7;
      ~basic_string<>();
      if (*param_1 == '\0') {
        pcStack_b0 = "off";
        pcStack_b4 = "option_box";
        puStack_b8 = (undefined *)0x79ba17;
        local_64 = FUN_0081cb40();
      }
      else {
        pcStack_b0 = "on";
        pcStack_b4 = "option_box";
        puStack_b8 = (undefined *)0x79ba00;
        local_64 = FUN_0081cb40();
      }
      local_84 = (undefined1 *)&uStack_c4;
      local_80 = basic_string<>(local_64);
      FUN_007c44a0();
      pcStack_b0 = (char *)0x79ba47;
      FUN_0073d020();
      local_8._0_1_ = 1;
      pcStack_b0 = (char *)0x79ba53;
      FUN_004180b0();
      local_8 = (uint)local_8._1_3_ << 8;
      pcStack_b0 = (char *)0x79ba62;
      FUN_00426bc0();
    }
  }
  local_8 = 0xffffffff;
  pcStack_b0 = (char *)0x79ba71;
  ~basic_string<>();
  ExceptionList = local_10;
  uStack_ac = 0x79ba86;
  FUN_0083e885();
  return;
}

