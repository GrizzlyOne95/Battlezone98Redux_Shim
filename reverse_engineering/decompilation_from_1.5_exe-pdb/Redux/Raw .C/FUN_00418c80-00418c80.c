
void __thiscall FUN_00418c80(int param_1,int param_2)

{
  char cVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  if (*(int *)(param_1 + 0x18) != 0) {
    if (*(int *)(param_1 + 0x38) < param_2) {
      param_2 = *(int *)(param_1 + 0x38);
    }
    else if (param_2 < -*(int *)(param_1 + 0x38)) {
      param_2 = -*(int *)(param_1 + 0x38);
    }
    cVar1 = FUN_00418820();
    if (cVar1 == '\0') {
      puVar3 = (undefined4 *)FUN_004200d0(param_2 + *(int *)(param_1 + 0x38));
      **(undefined4 **)(param_1 + 0x18) = *puVar3;
    }
    else {
      piVar2 = (int *)FUN_004200d0(param_2 + *(int *)(param_1 + 0x38));
      **(int **)(param_1 + 0x18) = -*piVar2;
    }
  }
  return;
}

