
int __thiscall FUN_00840960(undefined4 *param_1,short *param_2,uint param_3,int param_4)

{
  uint uVar1;
  undefined4 *puVar2;
  short *psVar3;
  int iVar4;
  short *psVar5;
  
  if ((param_4 != 0) && (uVar1 = param_1[4], uVar1 != 0)) {
    if (uVar1 <= param_3) {
      param_3 = uVar1 - 1;
    }
    puVar2 = param_1;
    if (7 < (uint)param_1[5]) {
      puVar2 = (undefined4 *)*param_1;
    }
    psVar5 = (short *)((int)puVar2 + param_3 * 2);
    while( true ) {
      if (param_4 != 0) {
        psVar3 = param_2;
        iVar4 = param_4;
        do {
          if (*psVar3 == *psVar5) {
            if (7 < (uint)param_1[5]) {
              param_1 = (undefined4 *)*param_1;
            }
            return (int)psVar5 - (int)param_1 >> 1;
          }
          psVar3 = psVar3 + 1;
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
      }
      psVar3 = (short *)Myptr();
      if (psVar5 == psVar3) break;
      psVar5 = psVar5 + -1;
    }
  }
  return -1;
}

