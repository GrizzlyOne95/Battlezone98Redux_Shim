
void __fastcall FUN_00477440(undefined4 *param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  int *piVar3;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084786b;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = Attachable::vftable;
  local_8 = 0;
  for (local_14 = 0; local_14 < (int)param_1[4]; local_14 = local_14 + 1) {
    piVar3 = (int *)FUN_004200d0(local_14);
    puVar1 = (undefined4 *)*piVar3;
    if ((puVar1 != (undefined4 *)0x0) && (puVar1 != (undefined4 *)0x0)) {
      (**(code **)*puVar1)(1);
    }
  }
  local_8 = 0xffffffff;
  FUN_0041fe20(uVar2);
  ExceptionList = local_10;
  return;
}

