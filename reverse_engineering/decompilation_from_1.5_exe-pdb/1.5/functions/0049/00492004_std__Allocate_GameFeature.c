/*
 * Entry: 00492004
 * Name: std::_Allocate<GameFeature_*>
 * Namespace: std
 * Signature: GameFeature * * _Allocate<GameFeature_*>(uint param_1, GameFeature * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameFeature ** __cdecl std::_Allocate<GameFeature_*>(uint param_1,GameFeature **param_2)

{
  GameFeature **ppGVar1;
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
  ppGVar1 = operator_new(param_1 << 2);
  return ppGVar1;
}
