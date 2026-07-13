
/* WARNING: Removing unreachable block (ram,0x006e9dea) */

void FUN_006e9da0(char *param_1,short param_2,undefined4 param_3,char param_4,char param_5)

{
  char cVar1;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  undefined4 uStack_1c8;
  undefined4 *puStack_1c4;
  code *pcStack_1c0;
  ushort uVar2;
  char *pcStack_1b8;
  shared_ptr<class___ExceptionPtr> *psStack_1b4;
  uint uStack_1b0;
  undefined4 auStack_19c [40];
  undefined4 local_fc [6];
  undefined1 local_e4 [16];
  undefined1 local_d4 [8];
  undefined1 *local_cc;
  undefined1 *local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined1 *local_b8;
  undefined1 local_b4 [8];
  undefined4 local_ac;
  undefined1 local_a8 [8];
  undefined1 local_a0 [8];
  undefined1 *local_98;
  code *local_94;
  char *local_90;
  code *local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  char *local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  char *local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 *local_44;
  int *local_40;
  shared_ptr<class___ExceptionPtr> local_3c [11];
  char local_31;
  int local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00854a62;
  local_10 = ExceptionList;
  uStack_1b0 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x899440;
  pcStack_1b8 = (char *)0x400;
  local_14 = uStack_1b0;
  FUN_006d08b0();
  if (param_2 == 0) {
    if (param_4 == '\0') {
      psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x8994e4;
      pcStack_1b8 = (char *)0x400;
      FUN_006d08b0();
      *(undefined2 *)(local_30 + 0x4bf0) = 0x3ed;
      psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x6e9ea6;
      FUN_0041f830();
    }
    else if (*(short *)(local_30 + 0x4c0c) == 0x3ed) {
      psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x8994b0;
      pcStack_1b8 = (char *)0x400;
      FUN_006d08b0();
      *(undefined2 *)(local_30 + 0x4bf0) = 1000;
      psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x6e9ef1;
      FUN_0041f830();
    }
    else {
      psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x899510;
      pcStack_1b8 = (char *)0x400;
      FUN_006d08b0();
      *(undefined2 *)(local_30 + 0x4bf0) = *(undefined2 *)(local_30 + 0x4c0c);
      psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)(local_30 + 0x4c10);
      pcStack_1b8 = (char *)0x6e9f37;
      FID_conflict_operator_();
    }
  }
  else {
    psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x89947c;
    pcStack_1b8 = (char *)0x400;
    FUN_006d08b0();
    *(short *)(local_30 + 0x4bf0) = param_2;
    psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)param_3;
    pcStack_1b8 = (char *)0x6e9e64;
    FID_conflict_operator_();
  }
  psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x1;
  pcStack_1b8 = (char *)0x3;
  FUN_00574400();
  local_8 = 0;
  if (&stack0x00000000 == (undefined1 *)0x1ac) {
    local_44 = (undefined4 *)0x0;
  }
  else {
    local_44 = auStack_19c;
  }
  psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)(local_30 + 0x4bf4);
  pcStack_1b8 = ", and reason: ";
  uVar2 = *(ushort *)(local_30 + 0x4bf0);
  pcStack_1c0 = (code *)0x899540;
  puStack_1c4 = local_44;
  uStack_1c8 = 0x6e9f94;
  this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
  pcStack_1c0 = (code *)0x6e9f9f;
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,uVar2);
  pcStack_1c0 = (code *)0x6e9fa5;
  pcStack_1b8 = (char *)FUN_004bc590();
  FUN_00574730();
  psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)local_2c;
  pcStack_1b8 = (char *)0x6e9fc0;
  psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)GetPolicy();
  local_8._0_1_ = 1;
  pcStack_1b8 = (char *)0x400;
  local_74 = psStack_1b4;
  local_68 = psStack_1b4;
  FUN_006d4480();
  local_8._0_1_ = 0;
  psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x6e9ff0;
  ~basic_string<>();
  psStack_1b4 = local_3c;
  pcStack_1b8 = (char *)0x6ea002;
  FUN_00421ec0();
  pcStack_1b8 = (char *)0x6ea009;
  FUN_006e1ae0();
  local_8._0_1_ = 2;
  psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x6ea015;
  cVar1 = FUN_006ab7d0();
  if (cVar1 == '\0') {
    psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x7;
    pcStack_1b8 = param_1;
    make_error_code();
    local_8 = (uint)local_8._1_3_ << 8;
    psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x6ea036;
    FUN_006ca8c0();
    local_8 = 0xffffffff;
    psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x6ea048;
    FUN_00417f10();
    goto LAB_006ea360;
  }
  psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x6ea05e;
  local_40 = (int *)FUN_00421ec0();
  pcStack_1c0 = (code *)0x6ea075;
  local_98 = (undefined1 *)&pcStack_1b8;
  local_bc = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                       ((shared_ptr<class___ExceptionPtr> *)&pcStack_1b8,local_3c);
  pcStack_1c0 = (code *)(uint)*(ushort *)(local_30 + 0x4bf0);
  puStack_1c4 = &local_7c;
  uStack_1c8 = 0x6ea0a0;
  (**(code **)(*local_40 + 0x54))();
  psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x6ea0a8;
  cVar1 = FUN_006ab7d0();
  if (cVar1 != '\0') {
    *(undefined4 *)param_1 = local_7c;
    *(undefined4 *)(param_1 + 4) = local_78;
    local_8 = (uint)local_8._1_3_ << 8;
    psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x6ea0c9;
    FUN_006ca8c0();
    local_8 = 0xffffffff;
    psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x6ea0db;
    FUN_00417f10();
    goto LAB_006ea360;
  }
  if (param_5 != '\0') {
    psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x1;
    pcStack_1b8 = (char *)0x6ea0f5;
    FUN_00421ec0();
    pcStack_1b8 = (char *)0x6ea0fc;
    FUN_006f2db0();
  }
  *(undefined4 *)(local_30 + 0xa20) = 2;
  if (param_4 != '\0') {
    *(undefined1 *)(local_30 + 0x4c38) = 1;
  }
  if (0 < *(int *)(local_30 + 0xa14)) {
    local_88 = FUN_006f8260;
    local_84 = 0;
    psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)local_a8;
    pcStack_1b8 = (char *)0x6ea14b;
    pcStack_1b8 = (char *)FUN_006e1540();
    local_8._0_1_ = 3;
    psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)_1_exref;
    pcStack_1c0 = local_88;
    puStack_1c4 = local_fc;
    uStack_1c8 = 0x6ea179;
    local_70 = pcStack_1b8;
    local_54 = pcStack_1b8;
    local_80 = FUN_006eadb0();
    local_8._0_1_ = 4;
    local_b8 = (undefined1 *)&uStack_1c8;
    local_5c = local_80;
    local_c4 = FUN_006eae00(local_80);
    psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)
                  FUN_006d4050(local_a0,*(undefined4 *)(local_30 + 0xa14));
    pcStack_1b8 = (char *)0x6ea1d7;
    local_64 = psStack_1b4;
    local_4c = psStack_1b4;
    FID_conflict_operator_();
    psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x6ea1e2;
    FUN_006ca8c0();
    local_8._0_1_ = 3;
    psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x6ea1f1;
    ~input_processor<>();
    local_8._0_1_ = 2;
    psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x6ea200;
    FUN_006ca8c0();
  }
  local_31 = 0;
  psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)(local_30 + 0xa2c);
  pcStack_1b8 = (char *)0x6ea218;
  FUN_006d1110();
  local_8 = CONCAT31(local_8._1_3_,5);
  local_cc = (undefined1 *)&pcStack_1b8;
  pcStack_1c0 = (code *)0x6ea230;
  local_c0 = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                       ((shared_ptr<class___ExceptionPtr> *)&pcStack_1b8,local_3c);
  FUN_006ea380();
  if (*(char *)(local_30 + 0x4ab8) == '\0') {
    psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x6ea25a;
    cVar1 = FUN_006e1c30();
    if (cVar1 != '\0') goto LAB_006ea26a;
    local_48 = 1;
  }
  else {
LAB_006ea26a:
    local_48 = 0;
  }
  local_31 = (char)local_48;
  local_8._0_1_ = 2;
  psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x6ea286;
  FUN_006d1140();
  if (local_31 != '\0') {
    local_94 = FUN_006e9190;
    local_90 = (char *)0x0;
    psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)local_b4;
    pcStack_1b8 = (char *)0x6ea2b5;
    psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)FUN_006e1540();
    local_8._0_1_ = 6;
    pcStack_1b8 = local_90;
    pcStack_1c0 = (code *)local_e4;
    puStack_1c4 = (undefined4 *)0x6ea2e0;
    local_6c = psStack_1b4;
    local_50 = psStack_1b4;
    local_60 = FUN_006eabe0();
    local_8._0_1_ = 7;
    local_c8 = (undefined1 *)&uStack_1c8;
    local_58 = local_60;
    local_ac = FUN_006eac20(local_60);
    FUN_006e1210(local_d4);
    local_8._0_1_ = 6;
    psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x6ea328;
    ~<>();
    local_8._0_1_ = 2;
    psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x6ea337;
    FUN_006ca8c0();
  }
  psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x6ea33f;
  FUN_006ab750();
  local_8 = (uint)local_8._1_3_ << 8;
  psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x6ea34b;
  FUN_006ca8c0();
  local_8 = 0xffffffff;
  psStack_1b4 = (shared_ptr<class___ExceptionPtr> *)0x6ea35d;
  FUN_00417f10();
LAB_006ea360:
  ExceptionList = local_10;
  uStack_1b0 = 0x6ea375;
  FUN_0083e885();
  return;
}

