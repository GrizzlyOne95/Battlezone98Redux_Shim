
void __fastcall FUN_00799c40(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  longlong lVar3;
  undefined1 local_44 [48];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085f6b8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_00426b10(0,0,0);
  local_8 = 0;
  FUN_00426a60(&DAT_02cf2000,0);
  local_8._0_1_ = 1;
  FUN_00426af0("multi.ini");
  FUN_00417fd0(local_44);
  local_8._0_1_ = 2;
  uVar2 = FUN_0041f870(uVar1);
  FUN_00426c30(uVar2);
  local_8._0_1_ = 1;
  ~basic_string<>();
  uVar2 = FUN_00426cf0("multi",&DAT_0089e770,0,0);
  FUN_007a3d80(uVar2);
  lVar3 = FUN_00822ea0();
  *(longlong *)(param_1 + 0x148) = lVar3 + 15000;
  FUN_0073d860(1);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_004180b0();
  local_8 = 0xffffffff;
  FUN_00426bc0();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

