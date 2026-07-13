
void __fastcall FUN_0045cb70(undefined4 *param_1)

{
  char cVar1;
  uint uVar2;
  int *piVar3;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_00847213;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = AiMission::vftable;
  local_8 = 1;
  while (cVar1 = FUN_0042d8f0(uVar2), cVar1 == '\0') {
    piVar3 = (int *)FUN_0045e220();
    if ((undefined4 *)*piVar3 != (undefined4 *)0x0) {
      (*(code *)**(undefined4 **)*piVar3)(1);
    }
  }
  FUN_00461f60();
  FUN_006a3700();
  if (DAT_00915694 == param_1) {
    DAT_00915694 = (undefined4 *)0x0;
  }
  local_8 = local_8 & 0xffffff00;
  FUN_004284d0();
  local_8 = 0xffffffff;
  FUN_005d7350();
  ExceptionList = local_10;
  return;
}

