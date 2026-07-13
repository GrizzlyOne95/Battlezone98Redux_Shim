/*
 * Entry: 004c7ced
 * Name: std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<0>::operator++
 * Namespace: std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<0>
 * Signature: _Const_iterator<0> * operator++(_Const_iterator<0> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Const_iterator<0> * __thiscall
std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<0>::operator++
          (_Const_iterator<0> *this)

{
  this->_Ptr = this->_Ptr->_Next;
  return this;
}
