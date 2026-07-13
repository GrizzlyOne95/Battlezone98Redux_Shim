
void FUN_006ce960(uint param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 extraout_var;
  undefined4 uVar5;
  
  while( true ) {
    if (param_1 == 0) {
      return;
    }
    uVar2 = param_1 - 1 >> 1;
    uVar3 = FUN_005111d0(uVar2);
    uVar5 = extraout_var;
    uVar4 = FUN_005111d0(param_1);
    cVar1 = FUN_006b2ad0(uVar4,uVar3,uVar2,uVar5);
    if (cVar1 == '\0') break;
    FUN_006d2300(param_1,uVar2);
    param_1 = uVar2;
  }
  return;
}

