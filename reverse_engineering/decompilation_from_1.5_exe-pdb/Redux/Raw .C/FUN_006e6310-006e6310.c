
void FUN_006e6310(void)

{
  char cVar1;
  undefined1 *puStack_fc;
  code *pcStack_f8;
  undefined4 uStack_f4;
  undefined1 *puStack_f0;
  undefined1 *puStack_ec;
  code *pcStack_e8;
  uint uStack_e4;
  undefined4 local_e0;
  undefined1 *local_dc;
  undefined1 *local_d8;
  undefined1 local_d4 [8];
  undefined1 local_cc [8];
  undefined1 local_c4 [8];
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined1 local_90 [12];
  undefined1 local_84 [56];
  undefined1 local_4c [56];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00853f79;
  local_10 = ExceptionList;
  uStack_e4 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  pcStack_e8 = (code *)0x400;
  puStack_ec = (undefined1 *)0x6e635b;
  local_14 = uStack_e4;
  cVar1 = FUN_006d4590();
  if (cVar1 != '\0') {
    pcStack_e8 = (code *)0x898d24;
    puStack_ec = (undefined1 *)0x400;
    puStack_f0 = (undefined1 *)0x6e637a;
    FUN_006d08b0();
  }
  pcStack_e8 = (code *)0x6e6385;
  FUN_0068b0a0();
  local_8._0_1_ = 1;
  pcStack_e8 = (code *)local_c4;
  puStack_ec = (undefined1 *)0x6e63a8;
  uStack_f4 = FUN_006d6530();
  local_8._0_1_ = 2;
  pcStack_e8 = _1_exref;
  puStack_ec = &stack0x00000004;
  puStack_f0 = local_90;
  pcStack_f8 = FUN_006e6df0;
  puStack_fc = local_4c;
  local_b0 = uStack_f4;
  local_a0 = uStack_f4;
  local_b8 = FUN_006deb60();
  local_8._0_1_ = 3;
  local_dc = (undefined1 *)&puStack_fc;
  local_9c = local_b8;
  local_bc = FUN_006f0b70(local_b8);
  pcStack_e8 = (code *)FUN_006d4050(local_d4,5000);
  puStack_ec = (undefined1 *)0x6e6455;
  local_ac = pcStack_e8;
  local_a8 = pcStack_e8;
  FID_conflict_operator_();
  pcStack_e8 = (code *)0x6e6460;
  FUN_006ca8c0();
  local_8._0_1_ = 2;
  pcStack_e8 = (code *)0x6e646c;
  FUN_006d4f70();
  local_8._0_1_ = 1;
  pcStack_e8 = (code *)0x6e647b;
  FUN_006ca8c0();
  pcStack_e8 = (code *)local_cc;
  puStack_ec = (undefined1 *)0x6e648d;
  uStack_f4 = FUN_006d6530();
  local_8._0_1_ = 4;
  pcStack_e8 = _1_exref;
  puStack_ec = &stack0x00000004;
  puStack_f0 = local_90;
  pcStack_f8 = FUN_006e6f50;
  puStack_fc = local_84;
  local_b4 = uStack_f4;
  local_a4 = uStack_f4;
  local_98 = FUN_006deb60();
  local_8._0_1_ = 5;
  local_d8 = (undefined1 *)&puStack_fc;
  local_94 = local_98;
  local_e0 = FUN_006f0b70(local_98);
  FUN_006bb6b0();
  local_8._0_1_ = 4;
  pcStack_e8 = (code *)0x6e6516;
  FUN_006d4f70();
  local_8._0_1_ = 1;
  pcStack_e8 = (code *)0x6e6525;
  FUN_006ca8c0();
  local_8 = (uint)local_8._1_3_ << 8;
  pcStack_e8 = (code *)0x6e6534;
  FUN_006ca8c0();
  local_8 = 0xffffffff;
  pcStack_e8 = (code *)0x6e6543;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x00000004);
  ExceptionList = local_10;
  uStack_e4 = 0x6e6558;
  FUN_0083e885();
  return;
}

