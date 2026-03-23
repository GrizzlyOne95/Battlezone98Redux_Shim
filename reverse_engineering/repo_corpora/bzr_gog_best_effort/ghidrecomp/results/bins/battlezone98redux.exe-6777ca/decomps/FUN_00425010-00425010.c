
undefined4 FUN_00425010(undefined4 param_1)

{
  undefined4 *puVar1;
  char *pcVar2;
  
  while( true ) {
    puVar1 = (undefined4 *)FUN_004242f0(param_1);
    pcVar2 = (char *)FUN_004242d0(*puVar1);
    if (*pcVar2 != '\0') break;
    puVar1 = (undefined4 *)FUN_004242f0(param_1);
    param_1 = *puVar1;
  }
  return param_1;
}

