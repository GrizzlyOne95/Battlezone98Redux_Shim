
void FUN_007fb340(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_98 [8];
  undefined1 local_90 [8];
  undefined1 local_88 [8];
  undefined1 local_80 [8];
  undefined1 local_78 [8];
  undefined1 local_70 [8];
  undefined1 local_68 [8];
  undefined1 local_60 [8];
  undefined1 local_58 [8];
  undefined1 local_50 [4];
  undefined1 local_4c [4];
  int local_48;
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008642a3;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  basic_string<>("unnamed-grammar");
  local_8 = 0;
  FUN_007d8b50(local_48 + 0x20,local_44);
  local_8._0_1_ = 2;
  ~basic_string<>(uVar1);
  basic_string<>("unnamed-rule");
  local_8._0_1_ = 3;
  FUN_007d8ba0(local_2c);
  local_8 = CONCAT31(local_8._1_3_,5);
  ~basic_string<>();
  uVar2 = FUN_007d9a70(local_80,&DAT_0260c14d,&DAT_008a1d80);
  uVar2 = FUN_007d9980(local_50,uVar2);
  uVar3 = FUN_007d9860(local_88,&DAT_008922f4,0);
  uVar2 = FUN_007d98b0(local_98,uVar3,uVar2);
  uVar2 = FUN_007d98b0(local_58,&DAT_0260c14d,&DAT_008716ea,&DAT_008716ea,uVar2);
  uVar2 = FUN_007d9980(local_4c,uVar2);
  uVar3 = FUN_007d9860(local_70,&DAT_008a1d8c,0);
  uVar2 = FUN_007d98b0(local_90,uVar3,uVar2);
  uVar2 = FUN_007d98b0(local_60,uVar2);
  uVar2 = FUN_007d98b0(local_68,&DAT_0260c139,uVar2);
  uVar2 = FUN_007d98b0(local_78,uVar2);
  FUN_007fc2b0(local_48 + 0x20,uVar2);
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

