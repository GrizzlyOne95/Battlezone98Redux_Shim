
undefined4 * FUN_004b7490(undefined4 *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 *puVar2;
  
  while (cVar1 = FUN_00420f10(&stack0x0000000c), cVar1 != '\0') {
    puVar2 = (undefined4 *)FUN_0042de50();
    cVar1 = FUN_004b6400(*puVar2);
    if (cVar1 != '\0') break;
    FUN_0042da80();
  }
  *param_1 = param_2;
  return param_1;
}

