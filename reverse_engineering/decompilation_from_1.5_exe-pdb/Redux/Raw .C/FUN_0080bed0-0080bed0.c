
undefined1
FUN_0080bed0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 local_14 [4];
  undefined1 local_10 [11];
  undefined1 local_5;
  
  FUN_007ecb50(&local_5,param_2);
  puVar3 = &local_5;
  uVar2 = __Cnd_init_in_situ(param_1,puVar3);
  cVar1 = FUN_0080c5a0(uVar2,puVar3);
  if (cVar1 == '\0') {
    puVar3 = (undefined1 *)FUN_0066f210();
    uVar2 = FUN_007ecc00(local_10,param_2,param_3,param_4,param_5,*puVar3);
    uVar2 = FUN_007ecbe0(local_14,param_1,uVar2);
    cVar1 = FUN_0080c710(uVar2);
    if (cVar1 == '\0') {
      return 0;
    }
  }
  return 1;
}

