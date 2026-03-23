
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0061dc10(undefined4 param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  uint local_1c;
  uint local_14;
  
  iVar2 = FUN_0062c840();
  bVar1 = true;
  switch(param_1) {
  case 0:
    break;
  default:
    bVar1 = false;
    break;
  case 10:
    break;
  case 0xb:
    FUN_005d48b0();
    break;
  case 0xe:
    iVar3 = FUN_00572a70();
    if (iVar3 == 0) {
      FUN_004fbd50();
    }
    break;
  case 0xf:
    iVar3 = FUN_00572a70();
    if (iVar3 == 0) {
      FUN_004fbe90();
    }
    break;
  case 0x15:
    local_14 = (uint)(DAT_008eaaac == 0);
    DAT_008eaaac = local_14;
    break;
  case 0x16:
    iVar3 = FUN_00572a70();
    if (iVar3 == 0) {
      FUN_00821050();
    }
    break;
  case 0x17:
    iVar3 = FUN_00572a70();
    if ((iVar3 == 0) && (DAT_009454b8 == 0)) {
      FUN_0081e0c0("Game End: Failure from Gamekey press\n");
      FUN_00434170(0);
    }
    break;
  case 0x18:
    iVar3 = FUN_00572a70();
    if ((iVar3 == 0) && (DAT_009454b8 == 0)) {
      FUN_0081e0c0("Game End: Success from Gamekey press\n");
      FUN_00434170(1);
    }
    break;
  case 0x19:
    iVar3 = FUN_00572a70();
    if ((iVar3 == 0) && (DAT_009454b8 == 0)) {
      FUN_0081e0c0("Game End: Quit from Gamekey press\n");
      FUN_00434170(2);
    }
    break;
  case 0x24:
  }
  iVar3 = FUN_00572a70();
  if ((iVar3 == 0) || (iVar2 != 0)) {
    if ((!bVar1) && (iVar3 = FUN_0062c850(), iVar3 == 0)) {
      switch(param_1) {
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
        iVar3 = FUN_0061a050();
        if (iVar3 == 0) {
          if (iVar2 == 0) {
            if (9 < DAT_008eaad8) {
              FUN_0061d120(0,9);
            }
          }
          else {
            FUN_0061d120(iVar2,param_1);
          }
        }
        break;
      case 6:
      case 7:
      case 8:
      case 9:
      case 0x2a:
        FUN_0061d120(iVar2,param_1);
        break;
      case 0x10:
        iVar2 = FUN_00572a70();
        if (iVar2 != 0) {
          FUN_00624690();
        }
        break;
      case 0x11:
        iVar2 = FUN_00572a70();
        if (iVar2 != 0) {
          FUN_00624380();
        }
        break;
      case 0x12:
        iVar2 = FUN_00572a70();
        if (iVar2 != 0) {
          FUN_0046cd10(1);
        }
        break;
      case 0x13:
        iVar2 = FUN_00572a70();
        if (iVar2 != 0) {
          FUN_0046cd10(0);
        }
        break;
      case 0x14:
        iVar2 = FUN_00572a70();
        if (iVar2 != 0) {
          FUN_00627dd0();
        }
        break;
      case 0x27:
        FUN_004f2e10();
        break;
      case 0x28:
        FUN_004f2e20();
        break;
      case 0x29:
        FUN_00437db0();
        break;
      case 0x2b:
        local_1c = (uint)(DAT_009183c0 == 0);
        DAT_009183c0 = local_1c;
        break;
      case 0x2c:
        if ((DAT_009454b8 != 0) && (iVar2 = FUN_00572a70(), iVar2 == 0)) {
          *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) ^ 1;
        }
      }
    }
    _DAT_00918434 = param_1;
  }
  return;
}

