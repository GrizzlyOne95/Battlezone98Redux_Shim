
undefined4 __thiscall FUN_005ef8b0(int param_1,undefined4 param_2)

{
  int iVar1;
  
  switch(param_2) {
  case 0:
    return 0;
  case 1:
    iVar1 = FUN_005ed5a0();
    if (iVar1 == 0) {
      if (*(int *)(param_1 + 0x18) == 1) {
        FUN_005f91e0(*(undefined4 *)(param_1 + 0x20),0,0);
      }
      else if (*(int *)(param_1 + 0x18) == 2) {
        FUN_005f91e0(*(undefined4 *)(param_1 + 0x20),1,0);
      }
      else {
        FUN_005f91e0(*(undefined4 *)(param_1 + 0x20),9,0);
      }
    }
    else {
      FUN_005f91e0(*(undefined4 *)(param_1 + 0x20),7,0);
    }
    FUN_004dbb40();
    return 0;
  case 2:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x20),0x15,0);
    *(undefined4 *)(param_1 + 0x1c) = 1;
    break;
  case 3:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x20),10,0);
    *(undefined4 *)(param_1 + 0x1c) = 2;
    break;
  case 5:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x20),0xc,0);
    *(undefined4 *)(param_1 + 0x1c) = 3;
    break;
  case 7:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x20),0x13,0);
    *(undefined4 *)(param_1 + 0x1c) = 4;
    break;
  case 8:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x20),0x14,0);
    *(undefined4 *)(param_1 + 0x1c) = 6;
    break;
  case 10:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x20),0xf,0);
    *(undefined4 *)(param_1 + 0x1c) = 7;
    break;
  case 0x11:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x20),0x11,0);
    *(undefined4 *)(param_1 + 0x1c) = 9;
    break;
  case 0x12:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x20),0x12,0);
    *(undefined4 *)(param_1 + 0x1c) = 8;
  }
  return 1;
}

