
undefined4 * FUN_00708a90(undefined4 *param_1,undefined4 param_2,undefined4 param_3,code *param_4)

{
  char cVar1;
  undefined1 *puVar2;
  
  while (cVar1 = operator!=<>(&param_2,&param_3), cVar1 != '\0') {
    puVar2 = (undefined1 *)FUN_006f25a0();
    cVar1 = (*param_4)(*puVar2);
    if (cVar1 != '\0') break;
    FUN_00710080();
  }
  *param_1 = param_2;
  return param_1;
}

