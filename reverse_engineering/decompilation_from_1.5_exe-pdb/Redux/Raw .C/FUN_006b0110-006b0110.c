
void __fastcall FUN_006b0110(undefined4 *param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_4c;
  undefined4 local_48 [2];
  undefined4 local_40 [2];
  undefined1 local_35 [5];
  undefined1 local_30 [10];
  undefined1 local_26;
  undefined1 local_25;
  uint local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850368;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004fbb60(local_14);
  uVar1 = FUN_006af3f0(2,1,6,local_30);
  FUN_006b0020(uVar1);
  local_8 = 0;
  iVar2 = get();
  if (iVar2 == -1) {
    FUN_006aba00(local_30,"socket_select_interrupter");
  }
  local_40[0] = 1;
  local_35[0] = 0;
  uVar1 = get(local_35,0xffff,4,local_40,4,local_30);
  FUN_006af470(uVar1);
  local_4c = 0x10;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_24 = 2;
  local_20 = FUN_006afff0(0x7f000001);
  local_24 = local_24 & 0xffff;
  uVar1 = get(&local_24,local_4c,local_30);
  iVar2 = FUN_006ae950(uVar1);
  if (iVar2 == -1) {
    FUN_006aba00(local_30,"socket_select_interrupter");
  }
  uVar1 = get(&local_24,&local_4c,local_30);
  iVar2 = FUN_006af7e0(uVar1);
  if (iVar2 == -1) {
    FUN_006aba00(local_30,"socket_select_interrupter");
  }
  local_20 = FUN_006afff0(0x7f000001);
  uVar1 = get(0x7fffffff,local_30);
  iVar2 = FUN_006aef90(uVar1);
  if (iVar2 == -1) {
    FUN_006aba00(local_30,"socket_select_interrupter");
  }
  uVar1 = FUN_006af3f0(2,1,6,local_30);
  FUN_006b0020(uVar1);
  local_8 = CONCAT31(local_8._1_3_,1);
  iVar2 = get();
  if (iVar2 == -1) {
    FUN_006aba00(local_30,"socket_select_interrupter");
  }
  uVar1 = get(&local_24,local_4c,local_30);
  iVar2 = FUN_006aec50(uVar1);
  if (iVar2 == -1) {
    FUN_006aba00(local_30,"socket_select_interrupter");
  }
  uVar1 = get(0,0,local_30);
  uVar1 = FUN_006ae8e0(uVar1);
  FUN_006b0020(uVar1);
  local_8 = CONCAT31(local_8._1_3_,2);
  iVar2 = get();
  if (iVar2 == -1) {
    FUN_006aba00(local_30,"socket_select_interrupter");
  }
  local_48[0] = 1;
  local_26 = 0;
  uVar1 = get(&local_26,0x8004667e,local_48,local_30);
  iVar2 = FUN_006af850(uVar1);
  if (iVar2 != 0) {
    FUN_006aba00(local_30,"socket_select_interrupter");
  }
  local_40[0] = 1;
  uVar1 = get(&local_26,6,1,local_40,4,local_30);
  FUN_006af470(uVar1);
  local_48[0] = 1;
  local_25 = 0;
  uVar1 = get(&local_25,0x8004667e,local_48,local_30);
  iVar2 = FUN_006af850(uVar1);
  if (iVar2 != 0) {
    FUN_006aba00(local_30,"socket_select_interrupter");
  }
  local_40[0] = 1;
  uVar1 = get(&local_25,6,1,local_40,4,local_30);
  FUN_006af470(uVar1);
  uVar1 = FUN_006b00c0();
  *param_1 = uVar1;
  uVar1 = FUN_006b00c0();
  param_1[1] = uVar1;
  local_8._0_1_ = 1;
  FUN_006b0040();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006b0040();
  local_8 = 0xffffffff;
  FUN_006b0040();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

