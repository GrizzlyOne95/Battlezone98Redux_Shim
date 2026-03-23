
undefined4 FUN_006f77a0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 local_34 [8];
  undefined1 local_2c [8];
  undefined1 local_24 [8];
  undefined1 local_1c [8];
  undefined1 local_14 [8];
  undefined1 local_c [8];
  
  FUN_006d7d50();
  cVar1 = operator!=<>(param_2,local_c);
  if (cVar1 == '\0') {
    puVar3 = local_24;
    uVar2 = FUN_006d7d70(local_2c,puVar3,param_3);
    FUN_006df140(local_34,param_2,uVar2);
    uVar2 = FUN_006d7dd0(puVar3);
    cVar1 = FUN_006ff6d0(uVar2);
    if (cVar1 != '\0') {
      FUN_006d7d70(param_1);
      return param_1;
    }
  }
  else {
    uVar2 = FUN_006d7da0(local_14,param_2,param_3);
    uVar2 = FUN_006df140(local_1c,uVar2);
    cVar1 = FUN_006df1b0(uVar2);
    if (cVar1 != '\0') {
      FUN_006d7da0(param_1);
      return param_1;
    }
  }
  FUN_006ff6f0(param_1,param_2,param_3);
  return param_1;
}

