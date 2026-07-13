/*
 * Entry: 00401f29
 * Name: std::_Allocate<std::_Aux_cont>
 * Namespace: std
 * Signature: _Aux_cont * _Allocate<std::_Aux_cont>(uint param_1, _Aux_cont * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Aux_cont * __cdecl std::_Allocate<std::_Aux_cont>(uint param_1,_Aux_cont *param_2)

{
  _Aux_cont *p_Var1;
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
  p_Var1 = operator_new(param_1 << 2);
  return p_Var1;
}
