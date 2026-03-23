
void __thiscall
FUN_007ff0b0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            )

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863628;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  cVar1 = FUN_004c85a0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (cVar1 != '\0') {
    uVar2 = FUN_007d7520();
    local_8 = 0;
    FUN_007df9f0(uVar2);
    local_8 = 0xffffffff;
    FUN_006ab660();
  }
  uVar2 = FUN_00417780(param_5);
  uVar2 = FUN_00417780(param_4,uVar2);
  uVar2 = FUN_00417780(param_3,uVar2);
  uVar2 = FUN_00417780(param_2,uVar2);
  iVar3 = FUN_007d9580(param_1 + 8,uVar2);
  (**(code **)(iVar3 + 4))();
  ExceptionList = local_10;
  return;
}

