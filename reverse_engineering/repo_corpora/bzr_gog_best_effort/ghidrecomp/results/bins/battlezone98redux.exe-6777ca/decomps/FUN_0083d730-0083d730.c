
void __thiscall FUN_0083d730(undefined4 *param_1,uint param_2)

{
  void *pvVar1;
  int iVar2;
  void *_Dst;
  
  _Dst = (void *)0x0;
  if (param_2 != 0) {
    if (param_2 < 0x40000000) {
      _Dst = operator_new(param_2 * 4);
      if (_Dst != (void *)0x0) goto LAB_0083d765;
    }
                    /* WARNING: Subroutine does not return */
    std::_Xbad_alloc();
  }
LAB_0083d765:
  memmove(_Dst,(void *)*param_1,param_1[1] - (int)*param_1 & 0xfffffffc);
  pvVar1 = (void *)*param_1;
  iVar2 = param_1[1];
  if (pvVar1 != (void *)0x0) {
    operator_delete(pvVar1);
  }
  *param_1 = _Dst;
  param_1[2] = (void *)((int)_Dst + param_2 * 4);
  param_1[1] = (void *)((int)_Dst + (iVar2 - (int)pvVar1 >> 2) * 4);
  return;
}

