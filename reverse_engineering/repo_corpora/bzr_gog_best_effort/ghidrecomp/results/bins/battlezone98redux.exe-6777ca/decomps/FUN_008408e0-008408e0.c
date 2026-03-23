
int __thiscall FUN_008408e0(undefined4 *param_1,short *param_2,uint param_3,int param_4)

{
  undefined4 *puVar1;
  short *psVar2;
  undefined4 *puVar3;
  int iVar4;
  short *psVar5;
  
  if ((param_4 != 0) && (param_3 < (uint)param_1[4])) {
    puVar3 = param_1;
    if (7 < (uint)param_1[5]) {
      puVar3 = (undefined4 *)*param_1;
    }
    puVar1 = param_1;
    if (7 < (uint)param_1[5]) {
      puVar1 = (undefined4 *)*param_1;
    }
    for (psVar5 = (short *)((int)puVar1 + param_3 * 2);
        psVar5 < (short *)((int)puVar3 + param_1[4] * 2); psVar5 = psVar5 + 1) {
      if (param_4 != 0) {
        psVar2 = param_2;
        iVar4 = param_4;
        do {
          if (*psVar2 == *psVar5) {
            if (7 < (uint)param_1[5]) {
              param_1 = (undefined4 *)*param_1;
            }
            return (int)psVar5 - (int)param_1 >> 1;
          }
          psVar2 = psVar2 + 1;
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
      }
    }
  }
  return -1;
}

