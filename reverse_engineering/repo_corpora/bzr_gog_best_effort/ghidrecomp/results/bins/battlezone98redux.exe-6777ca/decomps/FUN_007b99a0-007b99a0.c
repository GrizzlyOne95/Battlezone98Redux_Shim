
void __thiscall FUN_007b99a0(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 auStack_244 [80];
  undefined4 uStack_1f4;
  char *pcStack_1f0;
  char *pcStack_1ec;
  undefined *puStack_1e8;
  float fStack_1e4;
  undefined *puStack_1e0;
  int local_1b8 [4];
  undefined1 auStack_1a8 [172];
  undefined4 local_fc;
  undefined8 local_f8;
  undefined4 local_f0;
  undefined1 *local_ec;
  undefined1 *local_e0;
  undefined4 local_dc;
  locale local_d8 [4];
  undefined4 local_d4;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined *local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined *local_88;
  void *local_84;
  void *local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  void *local_70;
  void *local_6c;
  void *local_68;
  undefined1 *local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined1 *local_58;
  int local_54;
  int local_50;
  uint local_4c;
  int local_48;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00861644;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_4c = 0;
  local_48 = param_1;
  if (*(int *)(param_1 + 0x14c) != 0) {
    FUN_007ba270();
  }
  if (*(int *)(local_48 + 0x2f4) != -1) {
    FUN_007d2870();
  }
  *(undefined4 *)(local_48 + 0x2f4) = param_2;
  FUN_007d2870();
  if (*(int *)(local_48 + 0x178) == 0) {
    local_dc = FUN_0081cb40();
    local_90 = FUN_0081cb40();
    local_50 = 0x78;
    local_54 = 0xaa;
    local_80 = operator_new(0x1ec);
    local_8 = 0;
    if (local_80 == (void *)0x0) {
      local_7c = 0;
    }
    else {
      puStack_1e0 = &DAT_00873e10;
      fStack_1e4 = 1.1351403e-38;
      local_7c = FUN_007c2480();
    }
    local_a0 = local_7c;
    local_8 = 0xffffffff;
    *(undefined4 *)(local_48 + 0x178) = local_7c;
    FUN_007d3f20();
    FUN_007d2870();
    (**(code **)(**(int **)(local_48 + 0x178) + 0x40))();
    (**(code **)(**(int **)(local_48 + 0x178) + 0x3c))();
    FUN_007c2950();
    FUN_007c23e0();
    FUN_007d2110();
    local_84 = operator_new(0x1ec);
    local_8 = 1;
    if (local_84 == (void *)0x0) {
      local_5c = 0;
    }
    else {
      puStack_1e0 = (undefined *)(float)(local_54 + 0x7f);
      fStack_1e4 = (float)(local_50 + 0x197);
      puStack_1e8 = &DAT_00873de0;
      pcStack_1ec = (char *)0x7b9c76;
      local_5c = FUN_007c2480();
    }
    local_b8 = local_5c;
    local_8 = 0xffffffff;
    *(undefined4 *)(local_48 + 0x17c) = local_5c;
    FUN_007d3f20();
    FUN_007d2870();
    (**(code **)(**(int **)(local_48 + 0x17c) + 0x40))();
    (**(code **)(**(int **)(local_48 + 0x17c) + 0x3c))();
    FUN_007c2950();
    FUN_007c23e0();
    FUN_007d2110();
    local_68 = operator_new(0x930);
    local_8 = 2;
    if (local_68 == (void *)0x0) {
      local_78 = 0;
    }
    else {
      puStack_1e0 = (undefined *)0x43a90000;
      fStack_1e4 = (float)(local_54 + -0x14);
      puStack_1e8 = (undefined *)(float)(local_50 + 0x5a);
      pcStack_1ec = "MissionName";
      pcStack_1f0 = (char *)0x7b9dc3;
      local_78 = FUN_007cc390();
    }
    local_c8 = local_78;
    local_8 = 0xffffffff;
    *(undefined4 *)(local_48 + 0x180) = local_78;
    iVar1 = FUN_0081caf0();
    if (iVar1 == 0) {
      local_58 = &DAT_00915540;
    }
    else {
      local_58 = (undefined1 *)FUN_0081cb40();
    }
    local_f8 = FUN_0056f760();
    FUN_006ccf80();
    FUN_00574400();
    local_8 = 3;
    local_70 = operator_new(0x114);
    local_8._0_1_ = 4;
    if (local_70 == (void *)0x0) {
      local_60 = 0;
    }
    else {
      local_e0 = &stack0xfffffe24;
      puStack_1e0 = (undefined *)0x7b9e8e;
      local_fc = FUN_006ccb70();
      local_8._0_1_ = 5;
      puStack_1e0 = (undefined *)0x7b9eaf;
      local_98 = local_fc;
      puStack_1e0 = (undefined *)FUN_006ccef0();
      local_8 = CONCAT31(local_8._1_3_,6);
      local_4c = local_4c | 1;
      local_ec = auStack_244;
      local_b4 = puStack_1e0;
      local_88 = puStack_1e0;
      local_f0 = FUN_006cce50(1,&DAT_008961b8,&DAT_00896190,&DAT_00896290,&DAT_008961bc);
      local_8 = 7;
      local_bc = FUN_006cc7d0("%m/%d/%Y %I:%M:%S %p");
      local_60 = local_bc;
    }
    local_c4 = local_60;
    local_8 = 8;
    local_b0 = std::ios_base::getloc((ios_base *)((int)local_1b8 + *(int *)(local_1b8[0] + 4)));
    local_8 = 9;
    local_a8 = local_b0;
    local_d4 = FUN_006db9f0();
    local_8._0_1_ = 10;
    local_cc = local_d4;
    std::basic_ios<char,struct_std::char_traits<char>_>::imbue
              ((basic_ios<char,struct_std::char_traits<char>_> *)
               ((int)local_1b8 + *(int *)(local_1b8[0] + 4)),local_d8);
    FUN_00417b50();
    local_8._0_1_ = 9;
    FUN_00417b50();
    local_8 = CONCAT31(local_8._1_3_,8);
    FUN_00417b50();
    local_8 = 3;
    if ((local_4c & 1) != 0) {
      local_4c = local_4c & 0xfffffffe;
      FUN_006c3560();
    }
    if (&stack0x00000000 == (undefined1 *)0x1b8) {
      local_64 = (undefined1 *)0x0;
    }
    else {
      local_64 = auStack_1a8;
    }
    FUN_006dba70();
    local_94 = GetPolicy();
    local_8._0_1_ = 0xb;
    local_8c = local_94;
    FUN_0041f870();
    puStack_1e0 = (undefined *)0x7ba089;
    sprintf((char *)(local_48 + 0x188),"%s %s");
    local_8._0_1_ = 3;
    ~basic_string<>();
    (**(code **)(**(int **)(local_48 + 0x180) + 0x3c))();
    FUN_007d2110();
    local_6c = operator_new(0x930);
    local_8._0_1_ = 0xc;
    if (local_6c == (void *)0x0) {
      local_74 = 0;
    }
    else {
      puStack_1e0 = (undefined *)0x41a00000;
      fStack_1e4 = 338.0;
      puStack_1e8 = (undefined *)(float)local_54;
      pcStack_1ec = (char *)(float)(local_50 + 0x5a);
      pcStack_1f0 = "MissionTime";
      uStack_1f4 = 0x7ba148;
      local_74 = FUN_007cc390();
    }
    local_9c = local_74;
    local_8._0_1_ = 3;
    *(undefined4 *)(local_48 + 0x184) = local_74;
    local_ac = GetPolicy();
    local_8._0_1_ = 0xd;
    local_a4 = local_ac;
    FUN_0041f870();
    (**(code **)(**(int **)(local_48 + 0x184) + 0x3c))();
    local_8 = CONCAT31(local_8._1_3_,3);
    ~basic_string<>();
    FUN_007d2110();
    local_8 = 0xffffffff;
    FUN_00417f10();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

