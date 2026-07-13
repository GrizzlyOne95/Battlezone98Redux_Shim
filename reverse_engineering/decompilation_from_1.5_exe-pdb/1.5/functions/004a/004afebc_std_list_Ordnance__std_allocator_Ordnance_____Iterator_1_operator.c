/*
 * Entry: 004afebc
 * Name: std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Iterator<1>::operator++
 * Namespace: std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Iterator<1>
 * Signature: _Iterator<1> operator++(_Iterator<1> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> __thiscall
std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Iterator<1>::operator++
          (_Iterator<1> *this,int param_1)

{
  undefined4 extraout_EDX;
  _Iterator<1> _Var1;
  
  *(undefined4 *)param_1 = *(undefined4 *)this;
  *(undefined4 *)(param_1 + 4) = *(undefined4 *)&this->field_0x4;
  list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator++
            ((_Const_iterator<1> *)this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = param_1;
  return _Var1;
}
