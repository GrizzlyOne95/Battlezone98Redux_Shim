
void FUN_006955e0(int param_1,int param_2,int *param_3,int *param_4,int *param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = *(int *)(param_2 + 0x18) / *(int *)(param_1 + 0x88);
  iVar3 = *(int *)(param_2 + 0x14) / *(int *)(param_1 + 0x88);
  iVar1 = *(int *)(*(int *)(param_3[0x20] + iVar2 * 4) + iVar3 * 4);
  iVar4 = FUN_006a9020(*param_3,(int)*(char *)(param_2 + 0x10));
  if ((iVar4 == 1) && (iVar4 = FUN_006a9020(*param_3,(int)*(char *)(param_2 + 0x11)), iVar4 == 1)) {
    if (*(int *)(*(int *)(param_3[0x24] + iVar2 * 4) + iVar3 * 4) != 0) {
      *(int *)(iVar1 + 0x50) = *(int *)(iVar1 + 0x50) + 1;
      *param_4 = *param_4 + 1;
      *(undefined4 *)(iVar1 + 0x84) = *(undefined4 *)(param_2 + 4);
      iVar2 = FUN_00694a90(param_2,param_3);
      iVar3 = FUN_006a4060(param_2);
      if (iVar3 == 0) {
        *(int *)(iVar1 + 0x54) = *(int *)(iVar1 + 0x54) + iVar2;
      }
      if (*param_5 < *(int *)(iVar1 + 0x50)) {
        *param_5 = *(int *)(iVar1 + 0x50);
      }
    }
  }
  else if ((int)*(char *)(param_2 + 0x10) == *param_3) {
    FUN_00696080(param_3,*(undefined4 *)(param_2 + 0x14),*(undefined4 *)(param_2 + 0x18),
                 *(undefined1 *)(*(int *)(param_2 + 8) + 0x54));
    *(int *)(iVar1 + 0x58) = *(int *)(iVar1 + 0x58) + 1;
  }
  return;
}

