
void FUN_00830af4(int param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  undefined4 *puVar7;
  int local_c;
  
  if (*(char *)(*(int *)(param_1 + 0x10) + 0x15) != '\x02') {
    if (param_2 + 1U < 0x40000000) {
      puVar3 = (undefined4 *)FUN_00838869(param_1,0,0,param_2 << 2);
    }
    else {
      puVar3 = (undefined4 *)FUN_008388ab(param_1);
    }
    piVar1 = *(int **)(param_1 + 0x10);
    iVar4 = param_2;
    puVar7 = puVar3;
    if (0 < param_2) {
      for (; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar7 = 0;
        puVar7 = puVar7 + 1;
      }
    }
    local_c = 0;
    if (0 < piVar1[2]) {
      do {
        piVar6 = *(int **)(*piVar1 + local_c * 4);
        if (piVar6 != (int *)0x0) {
          do {
            piVar2 = (int *)*piVar6;
            uVar5 = piVar6[2] & param_2 - 1U;
            *piVar6 = puVar3[uVar5];
            puVar3[uVar5] = piVar6;
            piVar6 = piVar2;
          } while (piVar2 != (int *)0x0);
        }
        local_c = local_c + 1;
      } while (local_c < piVar1[2]);
    }
    FUN_00838869(param_1,*piVar1,piVar1[2] << 2,0);
    piVar1[2] = param_2;
    *piVar1 = (int)puVar3;
  }
  return;
}

