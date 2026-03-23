
undefined1 __thiscall FUN_00583430(int param_1,undefined4 param_2)

{
  undefined1 uVar1;
  
  switch(param_2) {
  case 3:
    uVar1 = FUN_00583a50();
    break;
  case 4:
    if (*(char *)(param_1 + 0x5c) == '\0') {
      uVar1 = FUN_00583a50();
    }
    else {
      uVar1 = FUN_0044bb90();
    }
    break;
  default:
    uVar1 = 0;
    break;
  case 7:
    uVar1 = FUN_00583bb0();
    break;
  case 8:
    if (*(char *)(param_1 + 0x5c) == '\0') {
      uVar1 = FUN_00583b90();
    }
    else {
      uVar1 = FUN_00583ac0();
    }
    break;
  case 9:
    uVar1 = FUN_00583a50();
    break;
  case 10:
  case 0xb:
    uVar1 = FUN_0044bb90();
  }
  return uVar1;
}

