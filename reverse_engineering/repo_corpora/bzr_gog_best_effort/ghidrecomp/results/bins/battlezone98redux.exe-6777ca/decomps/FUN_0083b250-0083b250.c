
void FUN_0083b250(int param_1,undefined4 *param_2)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  
  iVar1 = *(int *)(param_1 + 0x10);
  if (iVar1 < 0x114) {
    if (iVar1 == 0x113) {
      *param_2 = 2;
    }
    else {
      if (iVar1 == 0x7b) {
        FUN_00839e40(param_1,param_2);
        return;
      }
      if (iVar1 == 0x107) {
        *param_2 = 3;
      }
      else {
        if (iVar1 == 0x109) {
          FUN_00838ffd(param_1);
          FUN_0083998e(param_1,param_2,0,*(undefined4 *)(param_1 + 4));
          return;
        }
        if (iVar1 != 0x10d) {
LAB_0083b2e7:
          FUN_0083ad61(param_1,param_2);
          return;
        }
        *param_2 = 1;
      }
    }
    param_2[4] = 0xffffffff;
    param_2[5] = 0xffffffff;
    param_2[2] = 0;
  }
  else if (iVar1 == 0x117) {
    piVar2 = *(int **)(param_1 + 0x30);
    if (*(char *)(*piVar2 + 0x4a) == '\0') {
      FUN_008390b7(param_1,"cannot use \'...\' outside a vararg function");
    }
    *(byte *)(*piVar2 + 0x4a) = *(byte *)(*piVar2 + 0x4a) & 0xfb;
    uVar3 = FUN_0083c5d2(piVar2,0x25,0,1,0);
    param_2[4] = 0xffffffff;
    param_2[5] = 0xffffffff;
    *param_2 = 0xe;
    param_2[2] = uVar3;
  }
  else if (iVar1 == 0x11c) {
    param_2[4] = 0xffffffff;
    param_2[5] = 0xffffffff;
    param_2[2] = 0;
    *param_2 = 5;
    *(undefined8 *)(param_2 + 2) = *(undefined8 *)(param_1 + 0x18);
  }
  else {
    if (iVar1 != 0x11e) goto LAB_0083b2e7;
    FUN_00839dc7(param_1,param_2,*(undefined4 *)(param_1 + 0x18));
  }
  FUN_00838ffd(param_1);
  return;
}

