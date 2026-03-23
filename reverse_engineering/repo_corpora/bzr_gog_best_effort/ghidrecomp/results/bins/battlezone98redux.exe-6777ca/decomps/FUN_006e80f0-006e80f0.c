
undefined1 * FUN_006e80f0(undefined1 *param_1,undefined1 *param_2,code *param_3)

{
  char cVar1;
  
  while ((param_1 != param_2 && (cVar1 = (*param_3)(*param_1), cVar1 == '\0'))) {
    param_1 = param_1 + 1;
  }
  return param_1;
}

