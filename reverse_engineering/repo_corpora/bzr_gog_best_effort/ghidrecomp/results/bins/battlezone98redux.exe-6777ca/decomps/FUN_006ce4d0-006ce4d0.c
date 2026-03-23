
undefined4 FUN_006ce4d0(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 local_28 [32];
  undefined4 local_8;
  
  local_8 = param_2;
  switch(param_2) {
  case 0:
    uVar1 = FUN_006b2920(0);
    uVar2 = FUN_006b27e0(0);
    FUN_006d2040(uVar2,uVar1);
    break;
  case 1:
    uVar1 = FUN_006b2920(1);
    uVar2 = FUN_006b27e0(1);
    FUN_006d2040(uVar2,uVar1);
    break;
  case 2:
    uVar1 = FUN_006b2920(2);
    uVar2 = FUN_006b27e0(2);
    FUN_006d2040(uVar2,uVar1);
    break;
  case 3:
    uVar1 = FUN_006b28f0(0,0,0,0,0);
    uVar2 = FUN_006b27e0(3);
    FUN_006d2040(uVar2,uVar1);
    break;
  case 4:
    uVar1 = FUN_006b28f0(0,0,0,1,0);
    puVar3 = local_28;
    FUN_006b28f0(0x18,0,0,0,0);
    FUN_006d1fa0(puVar3,uVar1);
    puVar3 = local_28;
    uVar1 = FUN_006b27e0(4);
    FUN_006d2040(uVar1,puVar3);
    break;
  default:
    uVar1 = FUN_006b2920(0);
    uVar2 = FUN_006b27e0(0);
    FUN_006d2040(uVar2,uVar1);
  }
  return param_1;
}

