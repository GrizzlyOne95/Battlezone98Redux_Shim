/*
 * Entry: 0040e1d1
 * Name: std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::_Iterator<1>::operator++
 * Namespace: std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::_Iterator<1>
 * Signature: _Iterator<1> * operator++(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> * __thiscall
std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::_Iterator<1>::operator++
          (_Iterator<1> *this)

{
  list<AttackGroup_*,std::allocator<AttackGroup_*>_>::_Const_iterator<1>::operator++
            ((_Const_iterator<1> *)this);
  return this;
}
