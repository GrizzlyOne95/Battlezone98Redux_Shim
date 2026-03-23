
void * FUN_0082b7f5(undefined4 param_1,void *param_2,undefined4 param_3,size_t param_4)

{
  void *pvVar1;
  
  if (param_4 == 0) {
    free(param_2);
    pvVar1 = (void *)0x0;
  }
  else {
    pvVar1 = realloc(param_2,param_4);
  }
  return pvVar1;
}

