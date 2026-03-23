
void FUN_00840110(void)

{
  undefined1 auStack_a0 [24];
  undefined4 uStack_88;
  undefined1 *puStack_84;
  undefined1 auStack_80 [24];
  undefined4 uStack_68;
  undefined1 *puStack_64;
  undefined1 auStack_60 [24];
  undefined4 uStack_48;
  undefined1 *puStack_44;
  undefined1 auStack_40 [32];
  uint uStack_20;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00865628;
  local_c = ExceptionList;
  uStack_20 = DAT_008e7000 ^ (uint)&stack0xffffffe4;
  ExceptionList = &local_c;
  puStack_44 = auStack_40;
  uStack_48 = 0x840149;
  FUN_00840400();
  puStack_64 = auStack_60;
  local_4 = 0;
  uStack_68 = 0x840164;
  FUN_0083fec0();
  puStack_84 = auStack_80;
  uStack_88 = 0x840178;
  FUN_00840400();
  local_4 = CONCAT31(local_4._1_3_,2);
  FUN_0083fec0(auStack_a0);
  local_4 = 0xffffffff;
  FUN_00840c10();
  ExceptionList = local_c;
  return;
}

