
bool __fastcall FUN_005ede50(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  
  uVar2 = FUN_004cf880(*(undefined4 *)(param_1 + 0x30));
  *(undefined4 *)(param_1 + 0x30) = uVar2;
  cVar1 = FUN_00435a30();
  if (*(int *)(param_1 + 0x18) == 4) {
    piVar3 = (int *)FUN_00462630(*(undefined4 *)(param_1 + 0x30));
    uVar2 = (**(code **)(**(int **)(param_1 + 0x20) + 0x28))();
    *(undefined4 *)(param_1 + 0x4c) = uVar2;
    if (piVar3 == (int *)0x0) {
      *(undefined4 *)(param_1 + 0x48) = 0;
    }
    else {
      uVar2 = (**(code **)(*piVar3 + 0x28))();
      *(undefined4 *)(param_1 + 0x48) = uVar2;
    }
  }
  return cVar1 != '\0';
}

