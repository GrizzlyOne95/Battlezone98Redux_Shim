
void FUN_006f13a0(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  undefined1 auStack_174 [80];
  undefined4 uStack_124;
  undefined1 *puStack_120;
  undefined4 uStack_11c;
  undefined1 *puStack_118;
  undefined1 *puStack_114;
  uint uStack_110;
  undefined1 local_10c [8];
  undefined4 local_104;
  undefined1 *local_100;
  undefined1 local_fc [8];
  undefined4 local_f4;
  undefined1 local_f0 [4];
  undefined4 local_ec;
  allocator<char> *local_e8;
  undefined1 local_e4 [104];
  undefined1 local_7c [104];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00854ff3;
  local_10 = ExceptionList;
  uStack_110 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  puStack_114 = (undefined1 *)0x6f13dc;
  local_14 = uStack_110;
  cVar1 = FUN_006cb280();
  if (cVar1 == '\0') {
    puStack_114 = (undefined1 *)0x6f13f2;
    FUN_004fbb60();
    puStack_114 = local_f0;
    puStack_118 = (undefined1 *)0x6f1401;
    FUN_006d57b0();
    puStack_114 = local_fc;
    puStack_118 = local_f0;
    uStack_11c = 0x6f141a;
    uStack_11c = std::allocator<char>::allocator<char>(local_e8);
    puStack_120 = local_10c;
    uStack_124 = 0x6f142d;
    FUN_006cf300();
    uStack_124 = 0x6f1434;
    FUN_006f27a0();
    puStack_114 = (undefined1 *)0x6f143b;
    iVar2 = FUN_00667170();
    if (iVar2 != 0) {
      puStack_114 = (undefined1 *)param_2;
      puStack_118 = (undefined1 *)0x6f144f;
      FUN_006f4ac0();
      local_8 = 0;
      puStack_114 = local_fc;
      local_100 = auStack_174;
      local_104 = FUN_006f43c0(local_7c);
      puStack_114 = (undefined1 *)FUN_006f1520(local_e4);
      local_8._0_1_ = 1;
      puStack_118 = (undefined1 *)0x6f14ae;
      local_f4 = puStack_114;
      local_ec = puStack_114;
      FUN_006e4900();
      puStack_118 = (undefined1 *)0x6f14b5;
      FUN_006f1590();
      local_8 = (uint)local_8._1_3_ << 8;
      puStack_114 = (undefined1 *)0x6f14c4;
      FUN_006e4540();
      puStack_114 = (undefined1 *)0x6f14cc;
      FUN_00417c60();
      local_8 = 0xffffffff;
      puStack_114 = (undefined1 *)0x6f14db;
      FUN_006e4540();
      goto LAB_006f1503;
    }
  }
  puStack_114 = (undefined1 *)param_2;
  puStack_118 = (undefined1 *)param_1;
  uStack_11c = 0x6f14f0;
  uStack_11c = std::allocator<char>::allocator<char>(local_e8);
  puStack_120 = (undefined1 *)0x6f14fc;
  FUN_006cf300();
  puStack_120 = (undefined1 *)0x6f1503;
  FUN_006fe880();
LAB_006f1503:
  ExceptionList = local_10;
  uStack_110 = 0x6f1518;
  FUN_0083e885();
  return;
}

