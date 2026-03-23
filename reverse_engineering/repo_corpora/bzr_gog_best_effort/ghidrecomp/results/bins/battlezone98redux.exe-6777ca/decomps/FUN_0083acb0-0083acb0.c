
void FUN_0083acb0(int param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = 0;
  piVar1 = *(int **)(param_1 + 0x30);
  iVar2 = *piVar1;
  *(undefined1 *)(iVar2 + 0x4a) = 0;
  if (*(int *)(param_1 + 0x10) != 0x29) {
    do {
      if (*(int *)(param_1 + 0x10) == 0x117) {
        FUN_00838ffd(param_1);
        uVar3 = FUN_00838fac(param_1,&DAT_00870884,3,iVar5);
        FUN_0083abae(param_1,uVar3);
        *(undefined1 *)(iVar2 + 0x4a) = 7;
LAB_0083ad1e:
        iVar5 = iVar5 + 1;
      }
      else {
        if (*(int *)(param_1 + 0x10) == 0x11d) {
          uVar3 = FUN_0083b57b(param_1,iVar5);
          FUN_0083abae(param_1,uVar3);
          goto LAB_0083ad1e;
        }
        FUN_008390b7(param_1,"<name> or \'...\' expected");
      }
      if (*(char *)(iVar2 + 0x4a) != '\0') break;
      iVar4 = FUN_0083b6c3(param_1,0x2c);
    } while (iVar4 != 0);
  }
  FUN_008397cc(param_1,iVar5);
  *(byte *)(iVar2 + 0x49) = *(char *)((int)piVar1 + 0x32) - (*(byte *)(iVar2 + 0x4a) & 1);
  FUN_0083cd31(piVar1,*(undefined1 *)((int)piVar1 + 0x32));
  return;
}

