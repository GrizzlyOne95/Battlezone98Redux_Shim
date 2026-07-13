
undefined4 FUN_0083085a(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  char *pcVar3;
  int extraout_EDX;
  int iVar4;
  int extraout_EDX_00;
  int *extraout_EDX_01;
  int iVar5;
  bool bVar6;
  bool bVar7;
  
  bVar6 = false;
  bVar7 = false;
  iVar4 = *(int *)(param_2 + 8);
  iVar5 = param_1;
  if ((iVar4 != 0) && ((*(byte *)(iVar4 + 5) & 3) != 0)) {
    FUN_00830437(param_1,iVar4);
    iVar5 = extraout_EDX;
  }
  iVar4 = *(int *)(param_2 + 8);
  if ((((iVar4 != 0) && ((*(byte *)(iVar4 + 6) & 8) == 0)) &&
      (piVar2 = (int *)FUN_0083347b(iVar4,3,*(undefined4 *)(iVar5 + 200)), piVar2 != (int *)0x0)) &&
     (piVar2[2] == 4)) {
    pcVar3 = strchr((char *)(*piVar2 + 0x10),0x6b);
    bVar6 = pcVar3 != (char *)0x0;
    pcVar3 = strchr((char *)(*piVar2 + 0x10),0x76);
    bVar7 = pcVar3 != (char *)0x0;
    if ((bVar6) || (bVar7)) {
      *(byte *)(param_2 + 5) = (bVar7 * '\x02' | bVar6) << 3 | *(byte *)(param_2 + 5) & 0xe7;
      *(undefined4 *)(param_2 + 0x18) = *(undefined4 *)(param_1 + 0x2c);
      *(int *)(param_1 + 0x2c) = param_2;
      if (bVar6) {
        if (bVar7) {
          return 1;
        }
      }
      else if (bVar7) goto LAB_00830965;
    }
  }
  iVar4 = *(int *)(param_2 + 0x1c);
  if (iVar4 != 0) {
    iVar5 = iVar4 << 4;
    do {
      iVar5 = iVar5 + -0x10;
      iVar4 = iVar4 + -1;
      if ((3 < *(int *)(*(int *)(param_2 + 0xc) + 8 + iVar5)) &&
         (iVar1 = *(int *)(*(int *)(param_2 + 0xc) + iVar5), (*(byte *)(iVar1 + 5) & 3) != 0)) {
        FUN_00830437(param_1,iVar1);
        iVar4 = extraout_EDX_00;
      }
    } while (iVar4 != 0);
  }
LAB_00830965:
  iVar4 = 1 << (*(byte *)(param_2 + 7) & 0x1f);
  if (iVar4 != 0) {
    iVar5 = iVar4 << 5;
    do {
      iVar5 = iVar5 + -0x20;
      piVar2 = (int *)(*(int *)(param_2 + 0x10) + iVar5);
      iVar4 = iVar4 + -1;
      if (piVar2[2] == 0) {
        if (3 < piVar2[6]) {
          piVar2[6] = 0xb;
        }
      }
      else {
        if (((!bVar6) && (3 < piVar2[6])) && ((*(byte *)(piVar2[4] + 5) & 3) != 0)) {
          FUN_00830437(param_1,piVar2[4]);
          piVar2 = extraout_EDX_01;
        }
        if (((!bVar7) && (3 < piVar2[2])) && ((*(byte *)(*piVar2 + 5) & 3) != 0)) {
          FUN_00830437(param_1,*piVar2);
        }
      }
    } while (iVar4 != 0);
  }
  if ((!bVar6) && (!bVar7)) {
    return 0;
  }
  return 1;
}

