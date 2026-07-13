/*
 * Entry: 004d01cf
 * Name: std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::_Iterator<1>::operator++
 * Namespace: std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::_Iterator<1>
 * Signature: _Iterator<1> * operator++(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> * __thiscall
std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::_Iterator<1>::operator++(_Iterator<1> *this)

{
  list<AdjustItem_*,std::allocator<AdjustItem_*>_>::_Const_iterator<1>::operator++
            ((_Const_iterator<1> *)this);
  return this;
}
