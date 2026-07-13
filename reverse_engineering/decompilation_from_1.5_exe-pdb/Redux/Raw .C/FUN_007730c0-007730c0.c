
void FUN_007730c0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar2 = FUN_00772230();
  uVar3 = FUN_00772230(uVar2);
  cVar1 = FUN_007681a0(uVar3,uVar2);
  if (cVar1 != '\0') {
    FUN_007729e0(param_3,param_4,param_1,param_2);
  }
  uVar2 = FUN_00772230();
  uVar3 = FUN_00772230(uVar2);
  cVar1 = FUN_007681a0(uVar3,uVar2);
  if (cVar1 != '\0') {
    FUN_007729e0(param_5,param_6,param_3,param_4);
    uVar2 = FUN_00772230();
    uVar3 = FUN_00772230(uVar2);
    cVar1 = FUN_007681a0(uVar3,uVar2);
    if (cVar1 != '\0') {
      FUN_007729e0(param_3,param_4,param_1,param_2);
    }
  }
  return;
}

