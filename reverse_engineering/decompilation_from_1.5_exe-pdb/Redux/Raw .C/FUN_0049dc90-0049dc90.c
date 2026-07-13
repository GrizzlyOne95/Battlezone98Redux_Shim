
undefined4 __thiscall FUN_0049dc90(int param_1,undefined4 param_2)

{
  int iVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  
  switch(param_2) {
  case 0:
    uVar4 = 0;
    break;
  case 1:
    if (*(int *)(param_1 + 0x1c) == 0x10) {
      if (*(int *)(*(int *)(param_1 + 0x38) + 0x14c) == 2) {
        FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),7,0);
      }
      else {
        FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),1,0);
      }
      FUN_004dbb40();
      uVar4 = 0;
    }
    else {
      uVar4 = FUN_005fad00(param_2);
    }
    break;
  case 2:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),0x15,0);
    cVar2 = FUN_004723d0();
    if (cVar2 != '\0') {
      *(undefined4 *)(param_1 + 0x44) = 0;
      FUN_005aed80();
    }
    *(undefined4 *)(param_1 + 0x20) = 3;
    uVar4 = 1;
    break;
  default:
    uVar4 = FUN_005fad00(param_2);
    break;
  case 8:
    *(undefined4 *)(param_1 + 0x20) = 0x10;
    uVar4 = 1;
    break;
  case 9:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),8,0);
    FUN_004dbb40();
    uVar4 = 0;
    break;
  case 0x12:
    iVar1 = *(int *)(param_1 + 0x34);
    iVar3 = FUN_00462380();
    if (*(int *)(iVar1 + 0xd0) == iVar3) {
      FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),0x12,0);
      *(undefined4 *)(param_1 + 0x20) = 0xd;
    }
    else {
      FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),0x15,0);
      *(undefined4 *)(param_1 + 0x20) = 0x11;
    }
    uVar4 = 1;
    break;
  case 0x15:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),0x15,0);
    *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(*(int *)(param_1 + 0x34) + 0xe0);
    if (*(int *)(*(int *)(param_1 + 0x34) + 0xd4) == 0) {
      FUN_004dbb40();
      uVar4 = 0;
    }
    else {
      *(undefined4 *)(param_1 + 0x20) = 0x10;
      uVar4 = 1;
    }
  }
  return uVar4;
}

