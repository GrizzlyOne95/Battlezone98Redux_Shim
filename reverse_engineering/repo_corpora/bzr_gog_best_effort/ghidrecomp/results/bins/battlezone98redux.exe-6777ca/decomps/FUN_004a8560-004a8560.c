
undefined4 __thiscall FUN_004a8560(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  switch(param_2) {
  case 1:
    uVar1 = 0;
    break;
  case 2:
    FUN_004dbd60(5,DAT_00917afc);
    uVar1 = 1;
    break;
  default:
    uVar1 = 1;
    break;
  case 5:
    FUN_004dbce0(10);
    uVar1 = 1;
    break;
  case 6:
    FUN_004dbce0(0xb);
    uVar1 = 1;
    break;
  case 7:
    FUN_004dbd60(0x11,DAT_00917afc);
    uVar1 = 1;
    break;
  case 8:
    FUN_004dbd60(0x12,param_1);
    uVar1 = 1;
    break;
  case 0x18:
    FUN_004ae900();
    uVar1 = 1;
    break;
  case 0x19:
    FUN_004ae9f0();
    uVar1 = 1;
  }
  return uVar1;
}

