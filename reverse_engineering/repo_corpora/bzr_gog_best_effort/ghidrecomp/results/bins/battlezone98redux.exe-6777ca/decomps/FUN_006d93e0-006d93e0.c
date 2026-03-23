
undefined4 __thiscall FUN_006d93e0(undefined4 param_1,undefined2 param_2)

{
  char cVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  
  uVar2 = FUN_006b2540(param_1);
  switch(uVar2) {
  case 2:
    cVar1 = FUN_006e7d10(param_2);
    if (cVar1 == '\0') {
      uVar3 = 0x1c;
    }
    else {
      uVar3 = 0x1d;
    }
    break;
  default:
    uVar3 = 0x1f;
    break;
  case 4:
  case 6:
  case 9:
  case 0xb:
    uVar3 = 0x1e;
  }
  return uVar3;
}

