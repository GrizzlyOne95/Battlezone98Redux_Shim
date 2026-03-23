
void __fastcall FUN_0049b970(undefined4 *param_1)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008494a8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = CommTower::vftable;
  param_1[6] = CommTower::vftable;
  local_8 = 0;
  if (param_1[0x8f] == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_0049ba10(1);
  }
  param_1[0x66] = 0;
  local_8 = 0xffffffff;
  FUN_0047eab0(uVar1,uVar2);
  ExceptionList = local_10;
  return;
}

