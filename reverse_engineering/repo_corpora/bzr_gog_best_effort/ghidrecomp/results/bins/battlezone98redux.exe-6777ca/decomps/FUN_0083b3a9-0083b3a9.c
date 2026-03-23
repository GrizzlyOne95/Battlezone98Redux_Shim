
int FUN_0083b3a9(int *param_1,int param_2,undefined4 *param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  ushort *puVar3;
  int *piVar4;
  int iVar5;
  
  if (param_1 == (int *)0x0) {
    iVar1 = 8;
    param_3[4] = 0xffffffff;
    param_3[5] = 0xffffffff;
    *param_3 = 8;
    param_3[2] = 0xff;
  }
  else {
    iVar5 = *(byte *)((int)param_1 + 0x32) - 1;
    if (-1 < iVar5) {
      puVar3 = (ushort *)((int)param_1 + iVar5 * 2 + 0xac);
      do {
        if (param_2 == *(int *)((uint)*puVar3 * 0xc + *(int *)(*param_1 + 0x18))) goto LAB_0083b402;
        puVar3 = puVar3 + -1;
        iVar5 = iVar5 + -1;
      } while (-1 < iVar5);
    }
    iVar5 = -1;
LAB_0083b402:
    if (iVar5 < 0) {
      iVar1 = FUN_0083b3a9(param_1[2],param_2,param_3,0);
      if (iVar1 != 8) {
        uVar2 = FUN_0083a84e(param_1,param_2,param_3);
        param_3[2] = uVar2;
        iVar1 = 7;
        *param_3 = 7;
      }
    }
    else {
      iVar1 = 6;
      param_3[4] = 0xffffffff;
      param_3[5] = 0xffffffff;
      *param_3 = 6;
      param_3[2] = iVar5;
      if ((param_4 == 0) && (piVar4 = (int *)param_1[5], piVar4 != (int *)0x0)) {
        do {
          if ((int)(uint)*(byte *)(piVar4 + 2) <= iVar5) break;
          piVar4 = (int *)*piVar4;
        } while (piVar4 != (int *)0x0);
        if (piVar4 != (int *)0x0) {
          *(undefined1 *)((int)piVar4 + 9) = 1;
        }
      }
    }
  }
  return iVar1;
}

