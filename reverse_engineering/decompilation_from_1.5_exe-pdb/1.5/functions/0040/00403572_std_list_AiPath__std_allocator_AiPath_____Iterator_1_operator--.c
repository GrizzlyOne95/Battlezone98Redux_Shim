/*
 * Entry: 00403572
 * Name: std::list<AiPath_*,std::allocator<AiPath_*>_>::_Iterator<1>::operator--
 * Namespace: std::list<AiPath_*,std::allocator<AiPath_*>_>::_Iterator<1>
 * Signature: _Iterator<1> * operator--(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> * __thiscall
std::list<AiPath_*,std::allocator<AiPath_*>_>::_Iterator<1>::operator--(_Iterator<1> *this)

{
  list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator--
            ((_Const_iterator<1> *)this);
  return this;
}
