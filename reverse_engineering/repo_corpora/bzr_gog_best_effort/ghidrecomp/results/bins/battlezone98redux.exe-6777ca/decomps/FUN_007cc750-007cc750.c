
void __fastcall FUN_007cc750(int param_1)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  char *local_10;
  
  if (*(int *)(param_1 + 0x928) != 0) {
    FUN_00688110(*(undefined4 *)(param_1 + 0x928));
    *(undefined4 *)(param_1 + 0x928) = 0;
  }
  iVar10 = *(int *)(param_1 + 0x918);
  if (iVar10 == 1) {
    iVar5 = (int)(*(float *)(param_1 + 4) + *(float *)(param_1 + 0xc));
  }
  else if (iVar10 == 2) {
    iVar5 = (int)(*(float *)(param_1 + 0xc) * 0.5 + *(float *)(param_1 + 4));
  }
  else {
    iVar5 = (int)*(float *)(param_1 + 4);
  }
  iVar9 = *(int *)(param_1 + 0x914);
  if (iVar9 == 1) {
    iVar3 = (int)(*(float *)(param_1 + 8) + *(float *)(param_1 + 0x924) +
                 *(float *)(param_1 + 0x10) * 0.5);
  }
  else if (iVar9 == 2) {
    iVar3 = (int)(*(float *)(param_1 + 8) + *(float *)(param_1 + 0x924) + *(float *)(param_1 + 0x10)
                 );
  }
  else {
    iVar3 = (int)(*(float *)(param_1 + 8) + *(float *)(param_1 + 0x924));
  }
  uVar6 = *(int *)(param_1 + 0x91c) >> 0x18 & 0xff;
  if ((uVar6 != 0) && (param_1 != -0x144)) {
    local_10 = (char *)(param_1 + 0x144);
    iVar7 = param_1 + 0x145;
    do {
      cVar1 = *local_10;
      local_10 = local_10 + 1;
    } while (cVar1 != '\0');
    iVar8 = (int)local_10 - iVar7;
    if (iVar8 != 0) {
      if (*(char *)(param_1 + 0xe8) == '\0') {
        FUN_007d3f20(1);
      }
      uVar2 = FUN_007d3ee0(iVar8,iVar7,uVar6,iVar9,iVar10,iVar5,iVar3);
      uVar4 = FUN_00687de0(iVar5,iVar3,param_1 + 0x144,*(undefined4 *)(param_1 + 0x91c),
                           *(undefined4 *)(param_1 + 0x918),*(undefined4 *)(param_1 + 0x914),
                           *(undefined4 *)(param_1 + 0x920),uVar2);
      *(undefined4 *)(param_1 + 0x928) = uVar4;
    }
  }
  return;
}

