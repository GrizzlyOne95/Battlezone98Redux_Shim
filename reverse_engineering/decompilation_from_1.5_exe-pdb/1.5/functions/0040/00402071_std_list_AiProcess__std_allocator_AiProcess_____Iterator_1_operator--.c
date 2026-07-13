/*
 * Entry: 00402071
 * Name: std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Iterator<1>::operator--
 * Namespace: std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Iterator<1>
 * Signature: _Iterator<1> * operator--(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> * __thiscall
std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Iterator<1>::operator--(_Iterator<1> *this)

{
  list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::operator--
            ((_Const_iterator<1> *)this);
  return this;
}
