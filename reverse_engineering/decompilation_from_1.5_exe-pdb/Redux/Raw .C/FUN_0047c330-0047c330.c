
void FUN_0047c330(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_00417c70();
  if (param_1 == iVar1) {
    FUN_0047c540(6);
  }
  else {
    iVar1 = (**(code **)(*(int *)(param_1 + 0x18) + 4))();
    iVar2 = FUN_00461430();
    if (iVar1 == iVar2) {
      FUN_0047c540(4);
    }
  }
  return;
}

