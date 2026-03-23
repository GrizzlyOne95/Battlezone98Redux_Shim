
void __thiscall FUN_006dd720(undefined4 *param_1,undefined4 param_2,undefined1 param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  char *pcVar3;
  
  puVar1 = (undefined4 *)FUN_00422ea0(*param_1,param_3);
  uVar2 = FUN_006ef740(*puVar1);
  puVar1 = (undefined4 *)FUN_00422ea0();
  *puVar1 = uVar2;
  uVar2 = FUN_00416410();
  param_1[1] = uVar2;
  puVar1 = (undefined4 *)FUN_00422ea0();
  pcVar3 = (char *)FUN_004242d0(*puVar1);
  if (*pcVar3 == '\0') {
    puVar1 = (undefined4 *)FUN_00422ea0();
    uVar2 = FUN_00424310(*puVar1);
    puVar1 = (undefined4 *)FUN_00422e60();
    *puVar1 = uVar2;
    puVar1 = (undefined4 *)FUN_00422ea0();
    uVar2 = FUN_00425010(*puVar1);
    puVar1 = (undefined4 *)FUN_00422e80();
    *puVar1 = uVar2;
  }
  else {
    puVar1 = (undefined4 *)FUN_00422e60();
    *puVar1 = *param_1;
    puVar1 = (undefined4 *)FUN_00422e80();
    *puVar1 = *param_1;
  }
  return;
}

