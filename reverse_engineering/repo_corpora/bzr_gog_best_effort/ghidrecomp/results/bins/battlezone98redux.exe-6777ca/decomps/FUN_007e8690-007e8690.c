
void FUN_007e8690(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 local_e0 [20];
  uint local_cc;
  undefined1 local_c4 [100];
  undefined1 local_60 [76];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863d43;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_cc = 0;
  local_14 = uVar1;
  uVar2 = FUN_007e1640(param_2,param_3,param_4);
  FUN_007de810(uVar2);
  puVar4 = local_e0;
  uVar2 = param_4;
  uVar3 = FUN_007e3090(param_2,puVar4,param_4,uVar1);
  FUN_007e87f0(local_60,uVar3,puVar4,uVar2);
  local_8 = 0;
  puVar4 = local_60;
  uVar2 = FUN_007e3040(param_2,puVar4,param_4);
  FUN_007e8830(local_c4,uVar2,puVar4,param_4);
  local_8._0_1_ = 1;
  FUN_007de350(local_c4);
  local_cc = local_cc | 1;
  local_8 = (uint)local_8._1_3_ << 8;
  ~<>();
  local_8 = 0xffffffff;
  FUN_007dbc90();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

