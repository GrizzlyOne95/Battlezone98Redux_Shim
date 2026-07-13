/*
 * Entry: 0044fbd0
 * Name: std::_Allocate<Strip_*>
 * Namespace: std
 * Signature: Strip * * _Allocate<Strip_*>(uint param_1, Strip * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

Strip ** __cdecl std::_Allocate<Strip_*>(uint param_1,Strip **param_2)

{
  Strip **ppSVar1;
  exception local_8;
  
  if (param_1 == 0) {
    param_1 = 0;
  }
  else if ((uint)(0xffffffff / (ulonglong)param_1) < 4) {
    local_8._Ptr = (char *)0x0;
    local_8._padding_ = (int)&stdext::bad_alloc::_vftable_;
    if (_DAT_00225350 != (code *)0x0) {
      (*_DAT_00225350)(&local_8);
    }
    (**(code **)(local_8._padding_ + 8))();
    std::_Throw(&local_8);
  }
  ppSVar1 = operator_new(param_1 * 4);
  return ppSVar1;
}
