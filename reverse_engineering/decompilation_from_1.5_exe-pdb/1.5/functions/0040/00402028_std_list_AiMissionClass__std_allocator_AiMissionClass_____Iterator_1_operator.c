/*
 * Entry: 00402028
 * Name: std::list<AiMissionClass_*,std::allocator<AiMissionClass_*>_>::_Iterator<1>::operator++
 * Namespace: std::list<AiMissionClass_*,std::allocator<AiMissionClass_*>_>::_Iterator<1>
 * Signature: _Iterator<1> * operator++(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> * __thiscall
std::list<AiMissionClass_*,std::allocator<AiMissionClass_*>_>::_Iterator<1>::operator++
          (_Iterator<1> *this)

{
  list<AiMissionClass_*,std::allocator<AiMissionClass_*>_>::_Const_iterator<1>::operator++
            ((_Const_iterator<1> *)this);
  return this;
}
