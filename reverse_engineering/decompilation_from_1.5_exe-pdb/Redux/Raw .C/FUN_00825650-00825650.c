
int FUN_00825650(undefined4 param_1,int param_2,char *param_3,int param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  iVar1 = FUN_00826b40(param_1,param_3);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    FUN_00824a30(iVar1 + 0x20,param_2 + 8);
    *(undefined4 *)(iVar1 + 0x14) = *(undefined4 *)(param_2 + 0x60);
    iVar2 = _strnicmp(param_3,"null",4);
    if ((((iVar2 == 0) && (*(float *)(iVar1 + 0x20) == 0.0)) && (*(float *)(iVar1 + 0x24) == 0.0))
       && (*(float *)(iVar1 + 0x28) == 0.0)) {
      puVar4 = &DAT_008fe1e0;
      puVar5 = (undefined4 *)(iVar1 + 0x20);
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
    }
    iVar2 = *(int *)(param_2 + 0x5c);
    if (((iVar2 == 1) || (iVar2 == 3)) || (iVar2 == 6)) {
      uVar3 = FUN_004a78d0(param_2,*(undefined4 *)(param_2 + 0x5c));
      *(undefined4 *)(param_2 + 0x5c) = uVar3;
    }
    FUN_0062b940(iVar1,*(undefined4 *)(param_2 + 0x5c));
    if (param_4 == 0) {
      *(undefined4 *)(iVar1 + 0xac) = *(undefined4 *)(param_2 + 0x4c);
      *(undefined4 *)(iVar1 + 0xa0) = *(undefined4 *)(param_2 + 0x40);
      *(undefined4 *)(iVar1 + 0xa4) = *(undefined4 *)(param_2 + 0x44);
      *(undefined4 *)(iVar1 + 0xa8) = *(undefined4 *)(param_2 + 0x48);
      *(float *)(iVar1 + 0xb0) = *(float *)(iVar1 + 0xa0) - *(float *)(param_2 + 0x50);
      *(float *)(iVar1 + 0xbc) = *(float *)(iVar1 + 0xa0) + *(float *)(param_2 + 0x50);
      *(float *)(iVar1 + 0xb4) = *(float *)(iVar1 + 0xa4) - *(float *)(param_2 + 0x54);
      *(float *)(iVar1 + 0xc0) = *(float *)(iVar1 + 0xa4) + *(float *)(param_2 + 0x54);
      *(float *)(iVar1 + 0xb8) = *(float *)(iVar1 + 0xa8) - *(float *)(param_2 + 0x58);
      *(float *)(iVar1 + 0xc4) = *(float *)(iVar1 + 0xa8) + *(float *)(param_2 + 0x58);
      if (*(int *)(param_2 + 0x5c) == 0xf) {
        FUN_0062f3a0(iVar1,*(undefined4 *)(param_2 + 0x68),*(undefined4 *)(param_2 + 0x6c),
                     *(undefined4 *)(param_2 + 0x70));
        FUN_0062f400(iVar1,*(undefined4 *)(param_2 + 100));
      }
    }
  }
  return iVar1;
}

