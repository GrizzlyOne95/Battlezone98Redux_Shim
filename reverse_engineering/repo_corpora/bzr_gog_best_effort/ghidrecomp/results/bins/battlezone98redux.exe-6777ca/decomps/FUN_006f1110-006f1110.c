
void FUN_006f1110(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  undefined1 auStack_18c [88];
  undefined4 uStack_134;
  undefined1 *puStack_130;
  undefined4 uStack_12c;
  undefined1 *puStack_128;
  undefined1 *puStack_124;
  uint uStack_120;
  undefined1 local_11c [8];
  undefined4 local_114;
  undefined1 *local_110;
  undefined1 local_10c [8];
  undefined4 local_104;
  undefined1 local_100 [4];
  undefined4 local_fc;
  allocator<char> *local_f8;
  undefined1 local_f4 [112];
  undefined1 local_84 [112];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00854f33;
  local_10 = ExceptionList;
  uStack_120 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  puStack_124 = (undefined1 *)0x6f114c;
  local_14 = uStack_120;
  cVar1 = FUN_006cb280();
  if (cVar1 == '\0') {
    puStack_124 = (undefined1 *)0x6f1162;
    FUN_004fbb60();
    puStack_124 = local_100;
    puStack_128 = (undefined1 *)0x6f1171;
    FUN_006d57b0();
    puStack_124 = local_10c;
    puStack_128 = local_100;
    uStack_12c = 0x6f118a;
    uStack_12c = std::allocator<char>::allocator<char>(local_f8);
    puStack_130 = local_11c;
    uStack_134 = 0x6f119d;
    FUN_006cf300();
    uStack_134 = 0x6f11a4;
    FUN_006f27a0();
    puStack_124 = (undefined1 *)0x6f11ab;
    iVar2 = FUN_00667170();
    if (iVar2 != 0) {
      puStack_124 = (undefined1 *)param_2;
      puStack_128 = (undefined1 *)0x6f11bf;
      FUN_006f49e0();
      local_8 = 0;
      puStack_124 = local_10c;
      local_110 = auStack_18c;
      local_114 = FUN_006f4320(local_84);
      puStack_124 = (undefined1 *)FUN_006f1290(local_f4);
      local_8._0_1_ = 1;
      puStack_128 = (undefined1 *)0x6f121e;
      local_104 = puStack_124;
      local_fc = puStack_124;
      FUN_006e4900();
      puStack_128 = (undefined1 *)0x6f1225;
      FUN_006f1300();
      local_8 = (uint)local_8._1_3_ << 8;
      puStack_124 = (undefined1 *)0x6f1234;
      FUN_006e4520();
      puStack_124 = (undefined1 *)0x6f123c;
      FUN_00417c60();
      local_8 = 0xffffffff;
      puStack_124 = (undefined1 *)0x6f124b;
      FUN_006e4520();
      goto LAB_006f1273;
    }
  }
  puStack_124 = (undefined1 *)param_2;
  puStack_128 = (undefined1 *)param_1;
  uStack_12c = 0x6f1260;
  uStack_12c = std::allocator<char>::allocator<char>(local_f8);
  puStack_130 = (undefined1 *)0x6f126c;
  FUN_006cf300();
  puStack_130 = (undefined1 *)0x6f1273;
  FUN_006fe710();
LAB_006f1273:
  ExceptionList = local_10;
  uStack_120 = 0x6f1288;
  FUN_0083e885();
  return;
}

