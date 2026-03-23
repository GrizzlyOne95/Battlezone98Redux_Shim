
void FUN_007e9bf0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_e4 [12];
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  uint local_c8;
  undefined1 local_c1;
  undefined1 local_c0 [56];
  undefined1 local_88 [52];
  CDHtmlElementEventSink local_54 [64];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863dbe;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_c8 = 0;
  uVar3 = param_3;
  uVar2 = param_4;
  uVar1 = FUN_007e3090(param_2,param_3,param_4,local_14);
  local_d8 = FUN_007eac50(local_88,uVar1,uVar3,uVar2);
  local_8 = 0;
  local_d0 = local_d8;
  local_d4 = FUN_007eac90(local_c0,local_d8);
  local_8._0_1_ = 1;
  uVar3 = param_4;
  local_cc = local_d4;
  uVar2 = FUN_007e3040(param_2,param_3,param_4,local_d4);
  uVar3 = FUN_007e3510(local_e4,uVar2,param_3,uVar3);
  FUN_007eacc0(local_54,uVar3);
  local_8._0_1_ = 3;
  FUN_007dba50();
  local_8 = CONCAT31(local_8._1_3_,4);
  FUN_007dba30();
  local_c1 = 0;
  FUN_007eacf0(param_1,local_54,param_4);
  local_c8 = local_c8 | 1;
  local_8 = 0xffffffff;
  CDHtmlElementEventSink::~CDHtmlElementEventSink(local_54);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

