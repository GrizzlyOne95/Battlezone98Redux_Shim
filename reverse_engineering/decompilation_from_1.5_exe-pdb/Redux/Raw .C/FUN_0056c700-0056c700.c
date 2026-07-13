
void __fastcall FUN_0056c700(undefined4 *param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084b338;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = MultDMMission::vftable;
  param_1[0x15] = MultDMMission::vftable;
  local_8 = 0;
  if ((undefined4 *)param_1[0x19] == (undefined4 *)0x0) {
    uVar2 = 0;
  }
  else {
    uVar2 = (*(code *)**(undefined4 **)param_1[0x19])(1,uVar1);
  }
  puVar4 = (undefined4 *)param_1[0x18];
  if (puVar4 == (undefined4 *)0x0) {
    uVar3 = 0;
  }
  else {
    uVar3 = (**(code **)*puVar4)(1);
  }
  local_8 = 0xffffffff;
  FUN_0050b840(uVar1,uVar3,puVar4,uVar2);
  ExceptionList = local_10;
  return;
}

