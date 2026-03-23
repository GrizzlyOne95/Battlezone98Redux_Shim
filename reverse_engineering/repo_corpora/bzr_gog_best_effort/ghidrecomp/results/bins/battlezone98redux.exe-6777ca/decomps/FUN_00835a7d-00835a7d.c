
void * FUN_00835a7d(void *param_1,uint param_2,char *param_3,uint param_4)

{
  void *pvVar1;
  int iVar2;
  void *_Buf1;
  size_t _MaxCount;
  
  if (param_4 != 0) {
    if (param_2 < param_4) {
      param_1 = (void *)0x0;
    }
    else {
      _MaxCount = param_2 - (param_4 - 1);
      while ((_MaxCount != 0 &&
             (pvVar1 = memchr(param_1,(int)*param_3,_MaxCount), pvVar1 != (void *)0x0))) {
        _Buf1 = (void *)((int)pvVar1 + 1);
        iVar2 = memcmp(_Buf1,param_3 + 1,param_4 - 1);
        if (iVar2 == 0) {
          return pvVar1;
        }
        _MaxCount = (int)param_1 + (_MaxCount - (int)_Buf1);
        param_1 = _Buf1;
      }
      param_1 = (void *)0x0;
    }
  }
  return param_1;
}

