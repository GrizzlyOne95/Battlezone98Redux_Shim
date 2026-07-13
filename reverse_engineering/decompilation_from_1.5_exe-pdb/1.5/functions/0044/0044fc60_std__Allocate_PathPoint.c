/*
 * Entry: 0044fc60
 * Name: std::_Allocate<PathPoint>
 * Namespace: std
 * Signature: PathPoint * _Allocate<PathPoint>(uint param_1, PathPoint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

PathPoint * __cdecl std::_Allocate<PathPoint>(uint param_1,PathPoint *param_2)

{
  PathPoint *pPVar1;
  exception local_8;
  
  if (param_1 == 0) {
    pPVar1 = operator_new(0);
    return pPVar1;
  }
  if ((uint)(0xffffffff / (ulonglong)param_1) < 0x10) {
    local_8._Ptr = (char *)0x0;
    local_8._padding_ = (int)&stdext::bad_alloc::_vftable_;
    if (_DAT_00225350 != (code *)0x0) {
      (*_DAT_00225350)(&local_8);
    }
    (**(code **)(local_8._padding_ + 8))();
    std::_Throw(&local_8);
  }
  pPVar1 = operator_new(param_1 << 4);
  return pPVar1;
}
