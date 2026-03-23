
void __fastcall FUN_00799570(undefined4 *param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0085f5b6;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = cUI_Multiplayer_Create::vftable;
  local_8 = 1;
  DAT_0094555c = 0;
  if (param_1[0x73] == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_00799670(1);
  }
  iVar6 = param_1[0x72];
  if (iVar6 == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = FUN_007996a0(1);
  }
  iVar5 = param_1[0x71];
  if (iVar5 == 0) {
    uVar4 = 0;
  }
  else {
    uVar4 = FUN_007996d0(1);
  }
  local_8 = local_8 & 0xffffff00;
  FUN_0041fe20(uVar1,uVar4,iVar5,uVar3,iVar6,uVar2);
  local_8 = 0xffffffff;
  FUN_007d1eb0();
  ExceptionList = local_10;
  return;
}

