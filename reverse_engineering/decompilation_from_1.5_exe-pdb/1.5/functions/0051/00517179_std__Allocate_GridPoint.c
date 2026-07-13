/*
 * Entry: 00517179
 * Name: std::_Allocate<GridPoint>
 * Namespace: std
 * Signature: GridPoint * _Allocate<GridPoint>(uint param_1, GridPoint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GridPoint * __cdecl std::_Allocate<GridPoint>(uint param_1,GridPoint *param_2)

{
  GridPoint *pGVar1;
  undefined **in_ECX;
  exception local_c;
  
  local_c._padding_ = (int)in_ECX;
  local_c._Ptr = (char *)in_ECX;
  if (param_1 == 0) {
    param_1 = 0;
  }
  else if ((uint)(0xffffffff / (ulonglong)param_1) < 8) {
    local_c._Ptr = (char *)0x0;
    local_c._padding_ = (int)&stdext::bad_alloc::_vftable_;
    stdext::exception::_Raise(&local_c);
  }
  pGVar1 = operator_new(param_1 << 3);
  return pGVar1;
}
