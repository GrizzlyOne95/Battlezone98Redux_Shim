
void __fastcall FUN_00583c80(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  
  iVar2 = FUN_00417c70();
  if (iVar2 != 0) {
    (**(code **)(*(int *)(iVar2 + 0x18) + 4))();
    (**(code **)(*(int *)(*(int *)(param_1 + 0x34) + 0x18) + 4))();
    uVar1 = FUN_004db510(iVar2);
    *(undefined1 *)(param_1 + 0x5c) = uVar1;
  }
  FUN_005fb330();
  return;
}

