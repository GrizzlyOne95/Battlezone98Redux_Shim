
undefined4 __fastcall FUN_006bc240(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  
  uVar2 = FID_conflict__Immortalize<class_std::_Generic_error_category>(param_1);
  FUN_00416410(uVar2);
  cVar1 = FUN_006ab710(uVar2);
  if (cVar1 == '\0') {
    uVar2 = get();
    switch(uVar2) {
    case 3:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0x18:
    case 0x19:
      uVar2 = 0x3ea;
      break;
    case 4:
      uVar2 = 0x3f1;
      break;
    case 5:
    case 0x10:
      uVar2 = 0x3ef;
      break;
    default:
      uVar2 = 0x3f3;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

