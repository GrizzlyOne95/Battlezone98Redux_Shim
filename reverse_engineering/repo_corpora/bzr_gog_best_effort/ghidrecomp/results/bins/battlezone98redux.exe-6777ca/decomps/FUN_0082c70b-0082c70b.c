
uint FUN_0082c70b(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 0;
  iVar1 = *(int *)(param_1 + 0x10);
  switch(param_2) {
  case 0:
    *(undefined4 *)(iVar1 + 0x40) = 0xfffffffd;
    break;
  case 1:
    *(undefined4 *)(iVar1 + 0x40) = *(undefined4 *)(iVar1 + 0x44);
    break;
  case 2:
    FUN_008300aa(param_1);
    break;
  case 3:
    uVar3 = *(uint *)(iVar1 + 0x44) >> 10;
    break;
  case 4:
    uVar3 = *(uint *)(iVar1 + 0x44) & 0x3ff;
    break;
  case 5:
    uVar2 = *(uint *)(iVar1 + 0x44);
    if (uVar2 < (uint)(param_3 * 0x400)) {
      *(undefined4 *)(iVar1 + 0x40) = 0;
    }
    else {
      *(uint *)(iVar1 + 0x40) = uVar2 + param_3 * -0x400;
    }
    if (*(uint *)(iVar1 + 0x40) <= uVar2) {
      do {
        FUN_00830222(param_1);
        if (*(char *)(iVar1 + 0x15) == '\0') {
          return 1;
        }
      } while (*(uint *)(iVar1 + 0x40) <= *(uint *)(iVar1 + 0x44));
    }
    break;
  case 6:
    uVar3 = *(uint *)(iVar1 + 0x50);
    *(int *)(iVar1 + 0x50) = param_3;
    break;
  case 7:
    uVar3 = *(uint *)(iVar1 + 0x54);
    *(int *)(iVar1 + 0x54) = param_3;
    break;
  default:
    uVar3 = 0xffffffff;
  }
  return uVar3;
}

