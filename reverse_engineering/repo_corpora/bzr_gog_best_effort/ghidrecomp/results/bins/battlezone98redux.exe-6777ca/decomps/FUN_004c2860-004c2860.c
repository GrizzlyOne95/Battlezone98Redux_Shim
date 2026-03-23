
void __thiscall FUN_004c2860(int param_1,int *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  float fVar7;
  undefined4 uVar8;
  int local_14;
  int local_10;
  
  iVar4 = param_2[1] / 2;
  fVar7 = DAT_00920ef4;
  DAT_00920ef4 = DAT_00920ef4 + 0.03;
  FUN_0068af70(DAT_00917580,param_2[2] + -1,param_2[3] + -1,param_2[4] + 1,param_2[5] + 1,
               *(undefined4 *)(param_1 + 0x20),0);
  for (local_10 = 0; local_10 < 2; local_10 = local_10 + 1) {
    for (local_14 = 0; local_14 < iVar4; local_14 = local_14 + 1) {
      iVar6 = (local_10 * iVar4 + local_14) * 0x24 + *param_2;
      DAT_00920ef4 = fVar7 + 0.02;
      FUN_0068af70(DAT_00917580,*(undefined4 *)(iVar6 + 0x14),*(undefined4 *)(iVar6 + 0x18),
                   *(undefined4 *)(iVar6 + 0x1c),*(undefined4 *)(iVar6 + 0x20),
                   *(undefined4 *)(param_1 + 0x28),0);
      DAT_00920ef4 = fVar7 + 0.01;
      iVar5 = FUN_0049f100(DAT_009175a0,DAT_009175a4,iVar6 + 0x14);
      if ((iVar5 == 0) || (DAT_00919850 == '\0')) {
        FUN_0068c0f0(DAT_00917580,*(undefined4 *)(iVar6 + 0x10),*(int *)(iVar6 + 0x14) + 4,
                     *(int *)(iVar6 + 0x18) + 4,1,0);
        uVar1 = *(undefined4 *)(iVar6 + 0x14);
        uVar2 = *(undefined4 *)(iVar6 + 0x18);
        uVar8 = *(undefined4 *)(iVar6 + 0x1c);
        uVar3 = *(undefined4 *)(iVar6 + 0x20);
        FUN_0068af40(DAT_00917580,uVar1,uVar2,uVar1,uVar3,*(undefined4 *)(param_1 + 0x2c),0,iVar4,
                     fVar7,uVar8);
        FUN_0068af40(DAT_00917580,uVar1,uVar2,uVar8,uVar2,*(undefined4 *)(param_1 + 0x2c),0);
        FUN_0068af40(DAT_00917580,uVar8,uVar3,uVar1,uVar3,*(undefined4 *)(param_1 + 0x24),0);
        FUN_0068af40(DAT_00917580,uVar8,uVar3,uVar8,uVar2,*(undefined4 *)(param_1 + 0x24),0);
      }
      else {
        FUN_0068c0f0(DAT_00917580,*(undefined4 *)(iVar6 + 0x10),*(int *)(iVar6 + 0x14) + 6,
                     *(int *)(iVar6 + 0x18) + 6,1,0);
      }
    }
  }
  DAT_00920ef4 = fVar7;
  return;
}

