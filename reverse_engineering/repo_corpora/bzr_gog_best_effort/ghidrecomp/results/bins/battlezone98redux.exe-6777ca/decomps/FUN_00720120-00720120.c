
void * __thiscall FUN_00720120(undefined4 param_1,void *param_2,void *param_3,byte *param_4)

{
  char cVar1;
  void *pvVar2;
  
  cVar1 = FUN_00708cf0(param_2,param_4,param_1);
  if ((cVar1 != '\0') &&
     (pvVar2 = memchr(param_2,(uint)*param_4,(int)param_3 - (int)param_2), pvVar2 != (void *)0x0)) {
    param_3 = pvVar2;
  }
  return param_3;
}

