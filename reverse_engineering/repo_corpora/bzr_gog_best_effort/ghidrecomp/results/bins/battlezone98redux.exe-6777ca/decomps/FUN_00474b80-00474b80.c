
undefined4 __thiscall FUN_00474b80(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  switch(param_2) {
  case 0:
    return 0;
  case 1:
    cVar1 = FUN_004723d0();
    if (cVar1 == '\0') {
      if (*(int *)(param_1 + 0x18) == 4) {
        FUN_005f91e0(*(undefined4 *)(param_1 + 0x20),1,0);
      }
      else {
        cVar1 = FUN_004738b0();
        if (cVar1 == '\0') {
          FUN_005f91e0(*(undefined4 *)(param_1 + 0x20),8,0);
        }
        else {
          FUN_005f91e0(*(undefined4 *)(param_1 + 0x20),0,0);
        }
      }
    }
    else {
      FUN_005f91e0(*(undefined4 *)(param_1 + 0x20),7,0);
    }
    FUN_004dbb40();
    return 0;
  case 2:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x20),0x15,0);
    cVar1 = FUN_004723d0();
    if (cVar1 != '\0') {
      *(undefined4 *)(param_1 + 0x2c) = 0;
      FUN_005aed80();
    }
    *(undefined4 *)(param_1 + 0x1c) = 3;
    break;
  case 3:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x20),10,0);
    *(undefined4 *)(param_1 + 0x1c) = 4;
    break;
  case 5:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x20),0xc,0);
    *(undefined4 *)(param_1 + 0x1c) = 5;
    break;
  case 7:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x20),10,0);
    *(undefined4 *)(param_1 + 0x1c) = 1;
    break;
  case 10:
    if ((*(int *)(param_1 + 0x2c) != 0) && (cVar1 = FUN_004723d0(), cVar1 != '\0')) {
      return 0;
    }
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x20),0x18,0);
    uVar2 = FUN_00473920();
    *(undefined4 *)(param_1 + 0x2c) = uVar2;
    *(undefined4 *)(param_1 + 0x1c) = 6;
    break;
  case 0xb:
    if ((*(int *)(param_1 + 0x2c) != 0) && (cVar1 = FUN_004723d0(), cVar1 != '\0')) {
      return 0;
    }
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x20),0x10,0);
    uVar2 = FUN_00473900();
    *(undefined4 *)(param_1 + 0x2c) = uVar2;
    *(undefined4 *)(param_1 + 0x1c) = 6;
    break;
  case 0xc:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x20),0x11,0);
    *(undefined4 *)(param_1 + 0x1c) = 6;
    break;
  case 0xd:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x20),0x13,0);
    *(undefined4 *)(param_1 + 0x1c) = 6;
    break;
  case 0xe:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x20),0x14,0);
    *(undefined4 *)(param_1 + 0x1c) = 6;
    break;
  case 0x10:
    *(undefined4 *)(param_1 + 0x1c) = 8;
    break;
  case 0x12:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x20),0x12,0);
    *(undefined4 *)(param_1 + 0x1c) = 7;
    break;
  case 0x15:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x20),3,0);
    *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(*(int *)(param_1 + 0x20) + 0xe0);
    if (*(int *)(*(int *)(param_1 + 0x20) + 0xd4) != 0) {
      *(undefined4 *)(param_1 + 0x1c) = 6;
      return 1;
    }
    FUN_004dbb40();
    return 0;
  }
  return 1;
}

