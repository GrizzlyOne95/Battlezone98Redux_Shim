
void FUN_0082fe9e(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined8 uVar4;
  
  do {
    if (param_1 == 0) {
      return;
    }
    iVar2 = *(int *)(param_1 + 0x1c);
    if (((*(byte *)(param_1 + 5) & 0x10) != 0) && (iVar2 != 0)) {
      iVar3 = iVar2 << 4;
      do {
        iVar3 = iVar3 + -0x10;
        iVar1 = *(int *)(param_1 + 0xc) + iVar3;
        iVar2 = iVar2 + -1;
        uVar4 = FUN_0082ffca(iVar1,0);
        param_1 = (int)((ulonglong)uVar4 >> 0x20);
        if ((int)uVar4 != 0) {
          *(undefined4 *)(iVar1 + 8) = 0;
        }
      } while (iVar2 != 0);
    }
    iVar2 = 1 << (*(byte *)(param_1 + 7) & 0x1f);
    if (iVar2 != 0) {
      iVar3 = iVar2 << 5;
      do {
        iVar3 = iVar3 + -0x20;
        iVar1 = *(int *)(param_1 + 0x10) + iVar3;
        iVar2 = iVar2 + -1;
        if (*(int *)(iVar1 + 8) != 0) {
          uVar4 = FUN_0082ffca(iVar1 + 0x10,1);
          param_1 = (int)((ulonglong)uVar4 >> 0x20);
          if ((int)uVar4 == 0) {
            uVar4 = FUN_0082ffca(iVar1,0);
            param_1 = (int)((ulonglong)uVar4 >> 0x20);
            if ((int)uVar4 == 0) goto LAB_0082ff2f;
          }
          *(undefined4 *)(iVar1 + 8) = 0;
          if (3 < *(int *)(iVar1 + 0x18)) {
            *(undefined4 *)(iVar1 + 0x18) = 0xb;
          }
        }
LAB_0082ff2f:
      } while (iVar2 != 0);
    }
    param_1 = *(int *)(param_1 + 0x18);
  } while( true );
}

