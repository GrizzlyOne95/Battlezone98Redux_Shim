
void FUN_0083321b(int param_1,int *param_2,undefined4 param_3,int *param_4)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int local_20;
  int local_1c;
  int local_18;
  int *local_10;
  int local_c;
  int local_8;
  
  local_8 = 0;
  do {
    if (param_2[2] == 5) {
      iVar3 = *param_2;
      local_c = iVar3;
      local_10 = (int *)FUN_008310b4(param_1,iVar3,param_3);
      if ((((local_10[2] != 0) || (iVar1 = *(int *)(iVar3 + 8), iVar1 == 0)) ||
          ((*(byte *)(iVar1 + 6) & 2) != 0)) ||
         (piVar2 = (int *)FUN_0083347b(iVar1,1,*(undefined4 *)(*(int *)(param_1 + 0x10) + 0xc0)),
         iVar3 = local_c, piVar2 == (int *)0x0)) {
        *local_10 = *param_4;
        local_10[1] = param_4[1];
        local_10[2] = param_4[2];
        *(undefined1 *)(iVar3 + 6) = 0;
        if (param_4[2] < 4) {
          return;
        }
        if ((*(byte *)(*param_4 + 5) & 3) == 0) {
          return;
        }
        if ((*(byte *)(iVar3 + 5) & 4) == 0) {
          return;
        }
        FUN_00830000(param_1,iVar3);
        return;
      }
    }
    else {
      piVar2 = (int *)FUN_008334a2(param_1,param_2,1);
      if (piVar2[2] == 0) {
        FUN_0082dfec(param_1,param_2,"index");
      }
    }
    if (piVar2[2] == 6) {
      FUN_00831bea(param_1,piVar2,param_2,param_3,param_4);
      return;
    }
    param_2 = &local_20;
    local_20 = *piVar2;
    local_1c = piVar2[1];
    local_18 = piVar2[2];
    local_8 = local_8 + 1;
  } while (local_8 < 100);
  FUN_0082df5b(param_1,"loop in settable");
  return;
}

