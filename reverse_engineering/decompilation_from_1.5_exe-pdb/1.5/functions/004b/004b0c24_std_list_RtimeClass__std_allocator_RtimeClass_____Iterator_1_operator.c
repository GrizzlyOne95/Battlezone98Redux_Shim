/*
 * Entry: 004b0c24
 * Name: std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Iterator<1>::operator++
 * Namespace: std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Iterator<1>
 * Signature: _Iterator<1> * operator++(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> * __thiscall
std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Iterator<1>::operator++(_Iterator<1> *this)

{
  list<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Const_iterator<1>::operator++
            ((_Const_iterator<1> *)this);
  return this;
}
