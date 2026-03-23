
undefined4 __thiscall FUN_005c4140(int param_1,undefined4 param_2)

{
  int iVar1;
  
  switch(param_2) {
  case 0:
    return 0;
  case 1:
    if (*(int *)(param_1 + 0x1c) == 2) {
      FUN_005f91e0(*(undefined4 *)(param_1 + 0x28),1,0);
    }
    else if (*(int *)(param_1 + 0x1c) == 4) {
      if (*(int *)(param_1 + 0x58) == 0) {
        FUN_005f91e0(*(undefined4 *)(param_1 + 0x28),9,0);
      }
      else {
        iVar1 = FUN_005b53a0(*(undefined4 *)(param_1 + 0x58));
        if (iVar1 == 0) {
          FUN_005f91e0(*(undefined4 *)(param_1 + 0x28),4,0);
        }
        else if (iVar1 == 1) {
          FUN_005f91e0(*(undefined4 *)(param_1 + 0x28),5,0);
        }
        else {
          FUN_005f91e0(*(undefined4 *)(param_1 + 0x28),9,0);
        }
      }
    }
    else {
      FUN_005f91e0(*(undefined4 *)(param_1 + 0x28),9,0);
    }
    FUN_004dbb40();
    return 0;
  case 2:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x28),0x15,0);
    *(undefined4 *)(param_1 + 0x20) = 1;
    break;
  case 3:
  case 7:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x28),10,0);
    *(undefined4 *)(param_1 + 0x20) = 2;
    break;
  case 5:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x28),0xc,0);
    *(undefined4 *)(param_1 + 0x20) = 3;
    break;
  case 10:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x28),0xf,0);
    *(undefined4 *)(param_1 + 0x20) = 5;
    break;
  case 0x11:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x28),0x11,0);
    *(undefined4 *)(param_1 + 0x20) = 6;
    break;
  case 0x12:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x28),0x12,0);
    *(undefined4 *)(param_1 + 0x20) = 8;
    break;
  case 0x13:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x28),10,0);
    *(undefined4 *)(param_1 + 0x20) = 4;
  }
  return 1;
}

