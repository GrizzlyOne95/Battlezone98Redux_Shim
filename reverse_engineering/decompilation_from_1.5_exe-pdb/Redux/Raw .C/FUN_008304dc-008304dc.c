
undefined4 FUN_008304dc(int param_1)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  undefined4 uVar6;
  
  piVar2 = *(int **)(param_1 + 0x10);
  cVar1 = *(char *)((int)piVar2 + 0x15);
  if (cVar1 == '\0') {
    FUN_008302c4(param_1);
  }
  else if (cVar1 == '\x01') {
    if (piVar2[9] != 0) {
      uVar6 = FUN_00830353(piVar2);
      return uVar6;
    }
    FUN_0082fd56(param_1);
  }
  else {
    if (cVar1 == '\x02') {
      iVar3 = piVar2[6];
      iVar4 = piVar2[0x11];
      piVar2[6] = iVar3 + 1;
      FUN_008305c7(param_1,*piVar2 + iVar3 * 4,0xfffffffd);
      if (piVar2[2] <= piVar2[6]) {
        *(undefined1 *)((int)piVar2 + 0x15) = 3;
      }
      piVar2[0x12] = piVar2[0x12] + (piVar2[0x11] - iVar4);
      return 10;
    }
    if (cVar1 == '\x03') {
      iVar3 = piVar2[0x11];
      piVar5 = (int *)FUN_008305c7(param_1,piVar2[8],0x28);
      piVar2[8] = (int)piVar5;
      if (*piVar5 == 0) {
        FUN_0082fe33(param_1);
        *(undefined1 *)((int)piVar2 + 0x15) = 4;
      }
      piVar2[0x12] = piVar2[0x12] + (piVar2[0x11] - iVar3);
      return 400;
    }
    if (cVar1 == '\x04') {
      if (piVar2[0xc] != 0) {
        FUN_0082fc7c(param_1);
        if ((uint)piVar2[0x12] < 0x65) {
          return 100;
        }
        piVar2[0x12] = piVar2[0x12] - 100;
        return 100;
      }
      *(undefined1 *)((int)piVar2 + 0x15) = 0;
      piVar2[0x13] = 0;
    }
  }
  return 0;
}

