/*
 * Entry: 0052ea01
 * Name: std::_Allocate<ExplosionClass_*>
 * Namespace: std
 * Signature: ExplosionClass * * _Allocate<ExplosionClass_*>(uint param_1, ExplosionClass * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ExplosionClass ** __cdecl std::_Allocate<ExplosionClass_*>(uint param_1,ExplosionClass **param_2)

{
  ExplosionClass **ppEVar1;
  undefined **in_ECX;
  exception local_c;
  
  local_c._padding_ = (int)in_ECX;
  local_c._Ptr = (char *)in_ECX;
  if (param_1 == 0) {
    param_1 = 0;
  }
  else if ((uint)(0xffffffff / (ulonglong)param_1) < 4) {
    local_c._Ptr = (char *)0x0;
    local_c._padding_ = (int)&stdext::bad_alloc::_vftable_;
    stdext::exception::_Raise(&local_c);
  }
  ppEVar1 = operator_new(param_1 << 2);
  return ppEVar1;
}
