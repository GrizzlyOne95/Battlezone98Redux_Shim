
int FUN_0083bd73(int *param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  double *pdVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  
  iVar3 = param_1[4];
  pdVar2 = (double *)FUN_008310b4(iVar3,param_1[1],param_2);
  iVar1 = *param_1;
  piVar6 = (int *)(iVar1 + 0x28);
  iVar7 = *piVar6;
  if (*(int *)(pdVar2 + 1) == 3) {
    iVar3 = (int)*pdVar2;
  }
  else {
    iVar5 = param_1[10];
    *(undefined4 *)(pdVar2 + 1) = 3;
    *pdVar2 = (double)iVar5;
    if (*piVar6 < param_1[10] + 1) {
      uVar4 = FUN_008387f7(iVar3,*(undefined4 *)(iVar1 + 8),piVar6,0x10,0x3ffff,
                           "constant table overflow");
      *(undefined4 *)(iVar1 + 8) = uVar4;
    }
    if (iVar7 < *(int *)(iVar1 + 0x28)) {
      iVar5 = iVar7 << 4;
      do {
        *(undefined4 *)(iVar5 + 8 + *(int *)(iVar1 + 8)) = 0;
        iVar7 = iVar7 + 1;
        iVar5 = iVar5 + 0x10;
      } while (iVar7 < *(int *)(iVar1 + 0x28));
    }
    piVar6 = (int *)(param_1[10] * 0x10 + *(int *)(iVar1 + 8));
    *piVar6 = *param_3;
    piVar6[1] = param_3[1];
    piVar6[2] = param_3[2];
    if (((3 < param_3[2]) && ((*(byte *)(*param_3 + 5) & 3) != 0)) &&
       ((*(byte *)(iVar1 + 5) & 4) != 0)) {
      FUN_0083001b(iVar3,iVar1,*param_3);
    }
    iVar3 = param_1[10];
    param_1[10] = iVar3 + 1;
  }
  return iVar3;
}

