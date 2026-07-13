/*
 * Entry: 00404183
 * Name: std::list<AiTask_*,std::allocator<AiTask_*>_>::_Iterator<1>::operator++
 * Namespace: std::list<AiTask_*,std::allocator<AiTask_*>_>::_Iterator<1>
 * Signature: _Iterator<1> * operator++(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> * __thiscall
std::list<AiTask_*,std::allocator<AiTask_*>_>::_Iterator<1>::operator++(_Iterator<1> *this)

{
  list<AiTask_*,std::allocator<AiTask_*>_>::_Const_iterator<1>::operator++
            ((_Const_iterator<1> *)this);
  return this;
}
