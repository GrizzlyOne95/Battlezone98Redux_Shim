/*
 * Entry: 004800fe
 * Name: std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Iterator<1>::operator++
 * Namespace: std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Iterator<1>
 * Signature: _Iterator<1> * operator++(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> * __thiscall
std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Iterator<1>::operator++(_Iterator<1> *this)

{
  list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Const_iterator<1>::operator++
            ((_Const_iterator<1> *)this);
  return this;
}
