
undefined1
FUN_0080d1d0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 local_14 [4];
  undefined4 local_10;
  undefined1 local_6 [2];
  
  uVar2 = FUN_007edb50(param_2);
  local_10 = uVar2;
  uVar3 = __Cnd_init_in_situ(param_1,uVar2);
  cVar1 = FUN_0080ded0(uVar3,uVar2);
  if (cVar1 == '\0') {
    puVar4 = (undefined1 *)FUN_0066f210();
    uVar2 = FUN_007edbe0(local_14,param_2,param_3,param_4,param_5,*puVar4);
    uVar2 = FUN_0080e040(local_6,param_1,uVar2);
    cVar1 = FUN_006dc8e0(uVar2);
    if (cVar1 == '\0') {
      return 0;
    }
  }
  return 1;
}

