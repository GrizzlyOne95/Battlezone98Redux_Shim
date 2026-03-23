
void FUN_006e1100(void)

{
  char cVar1;
  undefined4 uStack_84;
  undefined1 *puStack_80;
  code *pcStack_7c;
  undefined4 uStack_78;
  undefined1 *puStack_74;
  code *pcStack_70;
  uint uStack_6c;
  undefined4 local_68;
  undefined1 local_64 [8];
  undefined1 *local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined1 local_44 [48];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00853ed8;
  local_10 = ExceptionList;
  uStack_6c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  pcStack_70 = (code *)0x400;
  puStack_74 = (undefined1 *)0x6e1142;
  local_14 = uStack_6c;
  cVar1 = FUN_006d4590();
  if (cVar1 != '\0') {
    pcStack_70 = (code *)0x898ed4;
    puStack_74 = (undefined1 *)0x400;
    uStack_78 = 0x6e115e;
    FUN_006d08b0();
  }
  pcStack_70 = (code *)local_64;
  puStack_74 = (undefined1 *)0x6e116a;
  uStack_78 = FUN_006d6530();
  local_8._0_1_ = 1;
  pcStack_70 = _1_exref;
  puStack_74 = &stack0x00000004;
  pcStack_7c = FUN_006e4b00;
  puStack_80 = local_44;
  uStack_84 = 0x6e1194;
  local_54 = uStack_78;
  local_50 = uStack_78;
  local_58 = FUN_006f0920();
  local_8._0_1_ = 2;
  local_5c = (undefined1 *)&uStack_84;
  local_4c = local_58;
  local_68 = FUN_006f0980(local_58);
  FUN_006bb5d0();
  local_8._0_1_ = 1;
  pcStack_70 = (code *)0x6e11cc;
  FUN_006e4380();
  local_8 = (uint)local_8._1_3_ << 8;
  pcStack_70 = (code *)0x6e11d8;
  FUN_006ca8c0();
  local_8 = 0xffffffff;
  pcStack_70 = (code *)0x6e11e7;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x00000004);
  ExceptionList = local_10;
  uStack_6c = 0x6e11fc;
  FUN_0083e885();
  return;
}

