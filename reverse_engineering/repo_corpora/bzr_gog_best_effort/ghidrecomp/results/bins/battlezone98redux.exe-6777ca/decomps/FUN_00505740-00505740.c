
void FUN_00505740(int *param_1,undefined4 param_2)

{
  char cVar1;
  
  cVar1 = *(char *)*param_1;
  *param_1 = *param_1 + 1;
  FUN_0082ccca(param_2,(int)cVar1);
  return;
}

