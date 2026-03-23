
undefined1 FUN_008167e0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 local_6 [2];
  
  uVar2 = __Cnd_init_in_situ(param_1);
  cVar1 = FUN_00816ab0(uVar2);
  if (cVar1 == '\0') {
    puVar3 = (undefined1 *)FUN_0066f210();
    uVar2 = FUN_00808d30(local_6,param_1,param_2,param_3,*puVar3);
    cVar1 = FUN_006dc8e0(uVar2);
    if (cVar1 == '\0') {
      return 0;
    }
  }
  return 1;
}

