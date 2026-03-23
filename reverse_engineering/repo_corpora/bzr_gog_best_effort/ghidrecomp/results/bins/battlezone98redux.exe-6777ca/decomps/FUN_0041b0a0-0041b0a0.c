
void __fastcall FUN_0041b0a0(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  uint *puVar3;
  uint local_48;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844cc0;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_48 = (uint)(*(char *)(param_1 + 0x98) != '\0');
  local_14 = uVar1;
  uVar2 = basic_string<>("MASTER:");
  local_8 = 0;
  uVar2 = FUN_00426a20(local_2c,uVar2,param_1 + 0x7c,uVar1);
  local_8._0_1_ = 1;
  puVar3 = (uint *)FUN_00421c70(uVar2);
  *puVar3 = local_48;
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

