
void __fastcall FUN_004f75c0(undefined4 *param_1)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084a7e8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = Inst4XMission::vftable;
  param_1[0x15] = Inst4XMission::vftable;
  local_8 = 0;
  if ((undefined4 *)param_1[0x18] == (undefined4 *)0x0) {
    uVar2 = 0;
  }
  else {
    uVar2 = (*(code *)**(undefined4 **)param_1[0x18])(1,uVar1);
  }
  local_8 = 0xffffffff;
  FUN_00508fe0(uVar1,uVar2);
  ExceptionList = local_10;
  return;
}

