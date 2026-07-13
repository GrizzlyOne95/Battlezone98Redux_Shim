/*
 * Entry: 00402182
 * Name: std::allocator<std::_Aux_cont>::allocate
 * Namespace: std::allocator<std::_Aux_cont>
 * Signature: _Aux_cont * allocate(allocator<std::_Aux_cont> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Aux_cont * __thiscall
std::allocator<std::_Aux_cont>::allocate(allocator<std::_Aux_cont> *this,uint param_1)

{
  _Aux_cont *p_Var1;
  
  p_Var1 = _Allocate<std::_Aux_cont>(param_1,(_Aux_cont *)0x0);
  return p_Var1;
}
