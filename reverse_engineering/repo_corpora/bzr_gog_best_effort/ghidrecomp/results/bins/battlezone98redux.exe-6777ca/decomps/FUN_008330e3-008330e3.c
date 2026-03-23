
void FUN_008330e3(int param_1,int *param_2,undefined4 param_3,undefined4 *param_4)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  int local_8;
  
  local_8 = 0;
  do {
    if (param_2[2] == 5) {
      iVar1 = *param_2;
      puVar2 = (undefined4 *)FUN_00830de6(iVar1,param_3);
      if ((((puVar2[2] != 0) || (iVar1 = *(int *)(iVar1 + 8), iVar1 == 0)) ||
          ((*(byte *)(iVar1 + 6) & 1) != 0)) ||
         (piVar3 = (int *)FUN_0083347b(iVar1,0,*(undefined4 *)(*(int *)(param_1 + 0x10) + 0xbc)),
         piVar3 == (int *)0x0)) {
        *param_4 = *puVar2;
        param_4[1] = puVar2[1];
        param_4[2] = puVar2[2];
        return;
      }
    }
    else {
      piVar3 = (int *)FUN_008334a2(param_1,param_2,0);
      if (piVar3[2] == 0) {
        FUN_0082dfec(param_1,param_2,"index");
      }
    }
    if (piVar3[2] == 6) {
      FUN_00831c7a(param_1,param_4,piVar3,param_2,param_3);
      return;
    }
    local_8 = local_8 + 1;
    param_2 = piVar3;
  } while (local_8 < 100);
  FUN_0082df5b(param_1,"loop in gettable");
  return;
}

