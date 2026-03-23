
undefined4 FUN_0058d650(float *param_1)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  char *pcVar8;
  float fVar9;
  
  fVar9 = param_1[2] * DAT_02cc50e4;
  iVar2 = FUN_0058be00(*param_1 * DAT_02cc50e4,fVar9);
  iVar3 = FUN_0058be00(fVar9);
  if ((((DAT_02ce99c0 <= iVar2) && (iVar2 < DAT_02ce99a0)) && (DAT_02cd9984 <= iVar3)) &&
     ((iVar3 < DAT_02ce99c4 && (DAT_0091814c != 0)))) {
    iVar4 = (int)((iVar3 - DAT_02cd9984) + (iVar3 - DAT_02cd9984 >> 0x1f & 0xfU)) >> 4;
    iVar5 = (int)((iVar2 - DAT_02ce99c0) + (iVar2 - DAT_02ce99c0 >> 0x1f & 0xfU)) >> 4;
    pcVar8 = (char *)((iVar4 * DAT_02a13c70 + iVar5) * 0x118 + DAT_0091814c);
    if (*pcVar8 == '\0') {
      FUN_00591710(iVar4,iVar5);
    }
    if (((*(int *)(pcVar8 + 0x10) <= iVar2) && (iVar2 < *(int *)(pcVar8 + 0x10) + 0x10)) &&
       ((*(int *)(pcVar8 + 0x14) <= iVar3 && (iVar3 < *(int *)(pcVar8 + 0x14) + 0x10)))) {
      bVar1 = pcVar8[(iVar2 - *(int *)(pcVar8 + 0x10)) +
                     (iVar3 - *(int *)(pcVar8 + 0x14)) * 0x10 + 0x18];
      uVar6 = size();
      if (bVar1 < uVar6) {
        puVar7 = (undefined4 *)FUN_004200d0((uint)bVar1);
        return *puVar7;
      }
    }
  }
  return 0;
}

