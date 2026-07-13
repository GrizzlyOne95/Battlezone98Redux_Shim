
undefined1 FUN_008082d0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined1 *puVar2;
  undefined4 uVar3;
  undefined1 local_14 [4];
  undefined4 local_10;
  
  local_10 = __Cnd_init_in_situ(param_1);
  cVar1 = FUN_00808c00(local_10);
  if (cVar1 == '\0') {
    puVar2 = (undefined1 *)FUN_0066f210();
    uVar3 = FUN_007eceb0(local_14,param_1,param_2,param_3,*puVar2);
    cVar1 = FUN_00808c30(uVar3);
    if (cVar1 == '\0') {
      return 0;
    }
  }
  return 1;
}

