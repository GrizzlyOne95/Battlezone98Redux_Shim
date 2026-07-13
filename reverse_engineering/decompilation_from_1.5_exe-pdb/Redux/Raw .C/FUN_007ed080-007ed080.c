
undefined1
FUN_007ed080(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined4 local_10;
  
  uVar2 = FUN_007edb50(param_2);
  local_10 = uVar2;
  uVar3 = __Cnd_init_in_situ(param_1,uVar2);
  cVar1 = FUN_007edf90(uVar3,uVar2);
  if (cVar1 == '\0') {
    puVar4 = (undefined1 *)FUN_0066f210();
    uVar2 = FUN_007edbe0(local_14,param_2,param_3,param_4,param_5,*puVar4);
    uVar2 = FUN_007edfe0(local_18,param_1,uVar2);
    cVar1 = FUN_007ee000(uVar2);
    if (cVar1 == '\0') {
      return 0;
    }
  }
  return 1;
}

