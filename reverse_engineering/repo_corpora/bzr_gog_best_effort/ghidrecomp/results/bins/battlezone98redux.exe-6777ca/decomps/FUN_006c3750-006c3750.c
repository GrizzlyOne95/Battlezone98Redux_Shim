
void FUN_006c3750(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uStack_100;
  undefined1 *puStack_fc;
  code *pcStack_f8;
  code *pcStack_f4;
  code *pcStack_f0;
  code *pcStack_ec;
  uint uStack_e8;
  undefined1 local_e4 [12];
  undefined1 local_d8 [12];
  undefined1 local_cc [12];
  undefined1 local_c0 [12];
  undefined1 local_b4 [12];
  undefined1 local_a8 [12];
  undefined1 local_9c [8];
  undefined1 *local_94;
  undefined1 *local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined1 *local_74;
  undefined1 local_70 [8];
  undefined1 *local_68;
  undefined4 local_64;
  undefined1 *local_60;
  undefined1 *local_5c;
  undefined1 *local_58;
  undefined4 local_54;
  undefined1 *local_50;
  int local_4c;
  int local_48;
  int local_44;
  code *local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  function<void___cdecl(void)> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00851d88;
  local_10 = ExceptionList;
  uStack_e8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  pcStack_ec = (code *)param_1;
  pcStack_f0 = (code *)0x6c3790;
  local_14 = uStack_e8;
  FUN_006dbcc0();
  if (DAT_009180d8 < 2) {
    pcStack_ec = (code *)0xffffffff;
    pcStack_f0 = (code *)0x6c37db;
    FUN_006cb940();
    pcStack_ec = (code *)0xffffffff;
    pcStack_f0 = (code *)0x6c37eb;
    FUN_006cb940();
  }
  else {
    pcStack_ec = (code *)0xffffffff;
    pcStack_f0 = (code *)0x6c37a9;
    FUN_006cb920();
    pcStack_ec = (code *)0xffffffff;
    pcStack_f0 = (code *)0x6c37b9;
    FUN_006cb920();
    pcStack_ec = (code *)0x10;
    pcStack_f0 = (code *)0x6c37c9;
    FUN_006cb940();
  }
  pcStack_ec = (code *)0x3a98;
  pcStack_f0 = (code *)0x6c37fe;
  FUN_006cbe00();
  local_40 = FUN_006c3730;
  local_74 = (undefined1 *)&uStack_100;
  local_88 = FUN_006dbd00(&local_40);
  FUN_006cbb40();
  pcStack_ec = (code *)0x7530;
  pcStack_f0 = (code *)0x6c383d;
  FUN_006cbdc0();
  pcStack_ec = (code *)0x6c3845;
  FUN_006caaf0();
  local_8 = 0;
  local_4c = local_30;
  pcStack_ec = _2_exref;
  pcStack_f0 = _1_exref;
  pcStack_f4 = (code *)&local_4c;
  pcStack_f8 = FUN_006c30f0;
  puStack_fc = local_e4;
  uStack_100 = 0x6c3875;
  uVar1 = FUN_006dbd70();
  local_58 = (undefined1 *)&uStack_100;
  local_78 = FUN_006dbdc0(uVar1);
  FUN_006cbc80();
  local_48 = local_30;
  pcStack_ec = _2_exref;
  pcStack_f0 = _1_exref;
  pcStack_f4 = (code *)&local_48;
  pcStack_f8 = FUN_006c31e0;
  puStack_fc = local_d8;
  uStack_100 = 0x6c38bc;
  uVar1 = FUN_006dbd70();
  local_60 = (undefined1 *)&uStack_100;
  local_7c = FUN_006dbdc0(uVar1);
  FUN_006cbbe0();
  pcStack_ec = (code *)(local_30 + 0x24);
  pcStack_f0 = (code *)0x6c38f0;
  FUN_006cbf30();
  local_34 = local_30;
  pcStack_ec = _2_exref;
  pcStack_f0 = _1_exref;
  pcStack_f4 = (code *)&local_34;
  pcStack_f8 = FUN_006bf2a0;
  puStack_fc = local_c0;
  uStack_100 = 0x6c3918;
  uVar1 = FUN_006dbd70();
  local_68 = (undefined1 *)&uStack_100;
  local_84 = FUN_006dbe30(uVar1);
  FUN_006cbd20();
  pcStack_ec = _2_exref;
  pcStack_f0 = _1_exref;
  pcStack_f4 = FUN_006be910;
  pcStack_f8 = (code *)local_9c;
  puStack_fc = (undefined1 *)0x6c3956;
  uVar1 = FUN_006dbea0();
  local_50 = (undefined1 *)&uStack_100;
  local_8c = FUN_006dbed0(uVar1);
  FUN_006bb850();
  local_38 = local_30;
  pcStack_ec = _1_exref;
  pcStack_f0 = (code *)&local_38;
  pcStack_f4 = FUN_006bee20;
  pcStack_f8 = (code *)local_a8;
  puStack_fc = (undefined1 *)0x6c399a;
  uVar1 = FUN_006dbf40();
  local_94 = (undefined1 *)&uStack_100;
  local_80 = FUN_006dbf80(uVar1);
  FUN_006cb960();
  local_3c = local_30;
  pcStack_ec = _1_exref;
  pcStack_f0 = (code *)&local_3c;
  pcStack_f4 = FUN_006bef70;
  pcStack_f8 = (code *)local_b4;
  puStack_fc = (undefined1 *)0x6c39dd;
  uVar1 = FUN_006dbf40();
  local_90 = (undefined1 *)&uStack_100;
  local_54 = FUN_006dbf80(uVar1);
  FUN_006cbaa0();
  local_44 = local_30;
  pcStack_ec = _1_exref;
  pcStack_f0 = (code *)&local_44;
  pcStack_f4 = FUN_006bf0d0;
  pcStack_f8 = (code *)local_cc;
  puStack_fc = (undefined1 *)0x6c3a21;
  uVar1 = FUN_006dbf40();
  local_5c = (undefined1 *)&uStack_100;
  local_64 = FUN_006dbf80(uVar1);
  FUN_006cba00();
  if (*(char *)(local_30 + 0x2e8) != '\0') {
    pcStack_ec = (code *)0x6c3a53;
    FUN_00764920();
  }
  pcStack_ec = (code *)0x6c3a5b;
  FUN_004fbb60();
  pcStack_ec = (code *)local_70;
  pcStack_f0 = (code *)0x6c3a67;
  FUN_006c35c0();
  local_8 = 0xffffffff;
  pcStack_ec = (code *)0x6c3a76;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>(local_2c);
  ExceptionList = local_10;
  uStack_e8 = 0x6c3a8b;
  FUN_0083e885();
  return;
}

