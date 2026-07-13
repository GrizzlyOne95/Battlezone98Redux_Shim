
void FUN_008302c4(int param_1)

{
  int iVar1;
  int iVar2;
  int extraout_EDX;
  int extraout_EDX_00;
  
  iVar1 = *(int *)(param_1 + 0x10);
  *(undefined4 *)(iVar1 + 0x24) = 0;
  *(undefined4 *)(iVar1 + 0x28) = 0;
  *(undefined4 *)(iVar1 + 0x2c) = 0;
  if ((*(byte *)(*(int *)(iVar1 + 0x70) + 5) & 3) != 0) {
    FUN_00830437(iVar1,*(int *)(iVar1 + 0x70));
    param_1 = extraout_EDX;
  }
  if ((3 < *(int *)(*(int *)(iVar1 + 0x70) + 0x50)) &&
     (iVar2 = *(int *)(*(int *)(iVar1 + 0x70) + 0x48), (*(byte *)(iVar2 + 5) & 3) != 0)) {
    FUN_00830437(iVar1,iVar2);
    param_1 = extraout_EDX_00;
  }
  if ((3 < *(int *)(*(int *)(param_1 + 0x10) + 0x68)) &&
     (iVar2 = *(int *)(*(int *)(param_1 + 0x10) + 0x60), (*(byte *)(iVar2 + 5) & 3) != 0)) {
    FUN_00830437(iVar1,iVar2);
  }
  FUN_00830294(iVar1);
  *(undefined1 *)(iVar1 + 0x15) = 1;
  return;
}

