
void FUN_0082fd56(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int extraout_EDX;
  int *piVar4;
  int *extraout_EDX_00;
  
  iVar1 = *(int *)(param_1 + 0x10);
  for (iVar2 = *(int *)(iVar1 + 0x8c); iVar2 != iVar1 + 0x78; iVar2 = *(int *)(iVar2 + 0x14)) {
    if ((((*(byte *)(iVar2 + 5) & 7) == 0) && (3 < (*(int **)(iVar2 + 8))[2])) &&
       (iVar3 = **(int **)(iVar2 + 8), (*(byte *)(iVar3 + 5) & 3) != 0)) {
      FUN_00830437(iVar1,iVar3);
      iVar2 = extraout_EDX;
    }
  }
  FUN_0083032f(iVar1);
  *(undefined4 *)(iVar1 + 0x24) = *(undefined4 *)(iVar1 + 0x2c);
  *(undefined4 *)(iVar1 + 0x2c) = 0;
  if ((*(byte *)(param_1 + 5) & 3) != 0) {
    FUN_00830437(iVar1,param_1);
  }
  FUN_00830294(iVar1);
  FUN_0083032f(iVar1);
  *(undefined4 *)(iVar1 + 0x24) = *(undefined4 *)(iVar1 + 0x28);
  *(undefined4 *)(iVar1 + 0x28) = 0;
  FUN_0083032f(iVar1);
  iVar2 = FUN_0083018d(param_1,0);
  piVar4 = *(int **)(iVar1 + 0x30);
  if (piVar4 != (int *)0x0) {
    do {
      iVar3 = *piVar4;
      *(byte *)(iVar3 + 5) = *(byte *)(iVar3 + 5) & 0xf8 | *(byte *)(iVar1 + 0x14) & 3;
      FUN_00830437(iVar1,iVar3);
      piVar4 = extraout_EDX_00;
    } while (extraout_EDX_00 != *(int **)(iVar1 + 0x30));
  }
  iVar3 = FUN_0083032f(iVar1);
  FUN_0082fe9e(*(undefined4 *)(iVar1 + 0x2c));
  *(byte *)(iVar1 + 0x14) = *(byte *)(iVar1 + 0x14) ^ 3;
  *(int *)(iVar1 + 0x20) = iVar1 + 0x1c;
  *(undefined4 *)(iVar1 + 0x18) = 0;
  *(undefined1 *)(iVar1 + 0x15) = 2;
  *(int *)(iVar1 + 0x48) = *(int *)(iVar1 + 0x44) - (iVar2 + iVar3);
  return;
}

