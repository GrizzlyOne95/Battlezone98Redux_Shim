
void FUN_00696170(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int local_1c;
  int local_8;
  
  iVar1 = *(int *)(param_2 + 0x598);
  for (local_8 = 0; local_8 < *(int *)(param_2 + 0x78); local_8 = local_8 + 1) {
    for (local_1c = 0; local_1c < *(int *)(param_2 + 0x7c); local_1c = local_1c + 1) {
      *(undefined4 *)(*(int *)(iVar1 + local_8 * 4) + local_1c * 4) = 0;
    }
  }
  for (local_8 = 0; local_8 < *(int *)(param_2 + 0x10); local_8 = local_8 + 1) {
    iVar2 = FUN_0069d590(param_2 + 8,local_8);
    iVar3 = *(int *)(iVar2 + 0x18) / *(int *)(param_1 + 0x88);
    iVar4 = *(int *)(iVar2 + 0x14) / *(int *)(param_1 + 0x88);
    FUN_00696080(param_2,*(undefined4 *)(iVar2 + 0x14),*(undefined4 *)(iVar2 + 0x18),
                 *(undefined1 *)(*(int *)(iVar2 + 8) + 0x54),
                 *(undefined4 *)(*(int *)(*(int *)(param_2 + 0x80) + iVar3 * 4) + iVar4 * 4));
    if (*(int *)(iVar2 + 0x24) == 0) {
      if (*(int *)(*(int *)(iVar1 + iVar3 * 4) + iVar4 * 4) == 0) {
        uVar5 = FUN_006a8850();
        *(undefined4 *)(*(int *)(iVar1 + iVar3 * 4) + iVar4 * 4) = uVar5;
        **(undefined4 **)(*(int *)(iVar1 + iVar3 * 4) + iVar4 * 4) = *(undefined4 *)(param_2 + 0x44)
        ;
        *(int *)(param_2 + 0x44) = *(int *)(param_2 + 0x44) + 1;
        *(int *)(*(int *)(*(int *)(iVar1 + iVar3 * 4) + iVar4 * 4) + 0x40) = param_2;
        FUN_006a8760(param_2 + 0x1c,"Schedule\\ai_team.cpp",0x4d2);
        uVar5 = FUN_0069d330(param_2 + 0x1c,*(undefined4 *)(*(int *)(iVar1 + iVar3 * 4) + iVar4 * 4)
                            );
        *(undefined4 *)(*(int *)(*(int *)(iVar1 + iVar3 * 4) + iVar4 * 4) + 0x44) = uVar5;
        FUN_006a8760(param_2 + 0x1c,"Schedule\\ai_team.cpp",0x4d6);
      }
      uVar5 = *(undefined4 *)(*(int *)(iVar1 + iVar3 * 4) + iVar4 * 4);
      FUN_006a8ae0(uVar5,iVar2,param_2);
      *(undefined4 *)(iVar2 + 0x24) = uVar5;
    }
  }
  return;
}

