
undefined4 FUN_006e4fd0(undefined4 param_1,undefined4 param_2,char param_3)

{
  undefined2 uVar1;
  longlong lVar2;
  undefined8 uVar3;
  undefined4 uVar4;
  
  uVar4 = 0;
  lVar2 = FUN_006e0e20();
  if ((param_3 == '\0') || (lVar2 != 0)) {
    uVar1 = FUN_006d1b60(lVar2,uVar4);
    uVar3 = imaxabs(lVar2,uVar1);
    FUN_006f1870(param_1,uVar3);
  }
  else {
    basic_string<>();
  }
  return param_1;
}

