
undefined4 __thiscall FUN_005fad00(int param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  switch(param_2) {
  case 0:
    return 0;
  case 1:
    if (*(int *)(*(int *)(param_1 + 0x34) + 0x228) == 1) {
      FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),6,0);
    }
    else {
      switch(*(undefined4 *)(param_1 + 0x1c)) {
      case 3:
        FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),0,0);
        break;
      case 4:
        FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),1,0);
        break;
      default:
        FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),9,0);
        break;
      case 7:
      case 0xf:
        FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),3,0);
        break;
      case 8:
        FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),2,0);
      }
    }
    FUN_004dbb40();
    return 0;
  case 2:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),0x15,0);
    *(undefined4 *)(param_1 + 0x20) = 3;
    break;
  case 3:
    if (*(int *)(*(int *)(param_1 + 0x34) + 0xd0) == 0) {
      FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),10,0);
    }
    else {
      FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),0xb,0);
    }
    *(undefined4 *)(param_1 + 0x20) = 4;
    break;
  case 4:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),0xe,0);
    *(undefined4 *)(param_1 + 0x20) = 7;
    break;
  case 5:
    iVar4 = FUN_00462630(*(undefined4 *)(*(int *)(param_1 + 0x34) + 0xd0));
    iVar2 = FUN_00417c70();
    if (iVar4 == iVar2) {
      FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),0xd,0);
    }
    else {
      FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),0xc,0);
    }
    *(undefined4 *)(param_1 + 0x20) = 8;
    break;
  default:
    *(undefined4 *)(param_1 + 0x20) = 3;
    break;
  case 7:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),0x15,0);
    *(undefined4 *)(param_1 + 0x20) = 0xe;
    break;
  case 10:
    if (*(char *)(param_1 + 0x4a) == '\0') {
      FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),0xf,0);
    }
    cVar1 = (**(code **)(**(int **)(param_1 + 0x34) + 0x68))();
    if (cVar1 != '\0') {
      FUN_00462590();
      iVar4 = FUN_005e0f70(3);
      if (iVar4 != 0) {
        cVar1 = FUN_004723d0();
        if ((cVar1 != '\0') || (iVar4 = FUN_00473890(), iVar4 != 0)) {
          *(undefined1 *)(param_1 + 0x4a) = 1;
          return 0;
        }
        cVar1 = FUN_00472700();
        if (cVar1 != '\0') {
          FUN_004dbd60(10,*(undefined4 *)(param_1 + 0x34));
          *(undefined4 *)(*(int *)(param_1 + 0x34) + 0xcc) = 0;
          *(undefined1 *)(param_1 + 0x4a) = 0;
          return 0;
        }
      }
    }
    *(undefined4 *)(param_1 + 0x20) = 10;
    break;
  case 0xb:
    if (*(char *)(param_1 + 0x4a) == '\0') {
      FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),0x10,0);
    }
    cVar1 = (**(code **)(**(int **)(param_1 + 0x34) + 0x68))();
    if (cVar1 != '\0') {
      uVar3 = FUN_00462590();
      iVar4 = FUN_005e0f70(3);
      if (iVar4 != 0) {
        cVar1 = FUN_004723d0(uVar3);
        if ((cVar1 != '\0') || (iVar4 = FUN_00473890(), iVar4 != 0)) {
          *(undefined1 *)(param_1 + 0x4a) = 1;
          return 0;
        }
        cVar1 = FUN_00472680();
        if (cVar1 != '\0') {
          FUN_004dbd60(0xb,*(undefined4 *)(param_1 + 0x34));
          *(undefined4 *)(*(int *)(param_1 + 0x34) + 0xcc) = 0;
          *(undefined1 *)(param_1 + 0x4a) = 0;
          return 0;
        }
      }
    }
    *(undefined4 *)(param_1 + 0x20) = 0xb;
    break;
  case 0xf:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),0xc,0);
    *(undefined4 *)(param_1 + 0x20) = 9;
    break;
  case 0x11:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),0x11,0);
    *(undefined4 *)(param_1 + 0x20) = 0xc;
    break;
  case 0x12:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),0x12,0);
    *(undefined4 *)(param_1 + 0x20) = 0xd;
    break;
  case 0x16:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),10,0);
    *(undefined4 *)(param_1 + 0x20) = 5;
    break;
  case 0x17:
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),10,0);
    *(undefined4 *)(param_1 + 0x20) = 6;
  }
  return 1;
}

