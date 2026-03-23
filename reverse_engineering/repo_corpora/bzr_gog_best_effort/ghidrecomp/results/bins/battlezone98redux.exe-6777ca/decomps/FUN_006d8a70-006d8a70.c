
void __thiscall FUN_006d8a70(int *param_1,undefined4 param_2)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  piVar2 = (int *)FUN_00417780(param_2);
  iVar1 = *piVar2;
  if (iVar1 != 0) {
    if (param_1[1] == 0) {
      *param_1 = iVar1;
    }
    else {
      FUN_006dc700(param_1 + 1,iVar1);
    }
    piVar2 = (int *)FUN_004242e0(param_2);
    param_1[1] = *piVar2;
    puVar3 = (undefined4 *)FUN_00417780(param_2);
    *puVar3 = 0;
    puVar3 = (undefined4 *)FUN_004242e0(param_2);
    *puVar3 = 0;
  }
  return;
}

