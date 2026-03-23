
int FUN_0083bac1(int *param_1,int param_2)

{
  short *psVar1;
  int *piVar2;
  undefined1 uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  
  iVar5 = *param_1;
  psVar1 = (short *)(iVar5 + 0x34);
  *psVar1 = *psVar1 + 1;
  if (200 < *(ushort *)(iVar5 + 0x34)) {
    FUN_0083bc6e(param_1,"code too deep");
  }
  iVar4 = FUN_0082fbf2(*param_1);
  piVar2 = *(int **)(*param_1 + 8);
  *piVar2 = iVar4;
  piVar2[2] = 9;
  iVar5 = *param_1;
  if (*(int *)(iVar5 + 0x1c) - *(int *)(iVar5 + 8) < 0x11) {
    FUN_0082f194(iVar5,1);
  }
  *(int *)(*param_1 + 8) = *(int *)(*param_1 + 8) + 0x10;
  iVar5 = FUN_0083bc1d(param_1);
  if (iVar5 == 0) {
    iVar5 = param_2;
  }
  *(int *)(iVar4 + 0x20) = iVar5;
  uVar6 = FUN_0083bbeb(param_1);
  *(undefined4 *)(iVar4 + 0x3c) = uVar6;
  uVar6 = FUN_0083bbeb(param_1);
  *(undefined4 *)(iVar4 + 0x40) = uVar6;
  uVar3 = FUN_0083b7c4(param_1);
  *(undefined1 *)(iVar4 + 0x48) = uVar3;
  uVar3 = FUN_0083b7c4(param_1);
  *(undefined1 *)(iVar4 + 0x49) = uVar3;
  uVar3 = FUN_0083b7c4(param_1);
  *(undefined1 *)(iVar4 + 0x4a) = uVar3;
  uVar3 = FUN_0083b7c4(param_1);
  *(undefined1 *)(iVar4 + 0x4b) = uVar3;
  iVar5 = FUN_0083bbeb(param_1);
  if (iVar5 + 1U < 0x40000000) {
    uVar6 = FUN_00838869(*param_1,0,0,iVar5 << 2);
  }
  else {
    uVar6 = FUN_008388ab(*param_1);
  }
  *(int *)(iVar4 + 0x2c) = iVar5;
  *(undefined4 *)(iVar4 + 0xc) = uVar6;
  FUN_0083b798(param_1,uVar6,iVar5 << 2);
  FUN_0083b7e1(param_1,iVar4);
  FUN_0083b96c(param_1,iVar4);
  iVar5 = FUN_0082de17(iVar4);
  if (iVar5 == 0) {
    FUN_0083bc6e(param_1,"bad code");
  }
  *(int *)(*param_1 + 8) = *(int *)(*param_1 + 8) + -0x10;
  *(short *)(*param_1 + 0x34) = *(short *)(*param_1 + 0x34) + -1;
  return iVar4;
}

