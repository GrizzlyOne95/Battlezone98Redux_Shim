/*
 * Entry: 0048aaf2
 * Name: std::_Allocate<BASE_STRUCT>
 * Namespace: std
 * Signature: BASE_STRUCT * _Allocate<BASE_STRUCT>(uint param_1, BASE_STRUCT * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BASE_STRUCT * __cdecl std::_Allocate<BASE_STRUCT>(uint param_1,BASE_STRUCT *param_2)

{
  BASE_STRUCT *pBVar1;
  undefined **in_ECX;
  exception local_c;
  
  local_c._padding_ = (int)in_ECX;
  local_c._Ptr = (char *)in_ECX;
  if (param_1 == 0) {
    param_1 = 0;
  }
  else if ((uint)(0xffffffff / (ulonglong)param_1) < 6) {
    local_c._Ptr = (char *)0x0;
    local_c._padding_ = (int)&stdext::bad_alloc::_vftable_;
    stdext::exception::_Raise(&local_c);
  }
  pBVar1 = operator_new(param_1 * 6);
  return pBVar1;
}
