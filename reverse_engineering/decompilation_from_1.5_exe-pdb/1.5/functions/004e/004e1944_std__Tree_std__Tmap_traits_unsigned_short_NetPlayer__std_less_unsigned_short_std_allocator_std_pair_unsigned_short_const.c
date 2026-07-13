/*
 * Entry: 004e1944
 * Name: std::_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>::_Tidy
 * Namespace: std::_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
 * Signature: void _Tidy(_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::
_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
::_Tidy(_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
        *this)

{
  const_iterator cVar1;
  const_iterator cVar2;
  const_iterator local_14;
  const_iterator local_c;
  
  const_iterator::const_iterator(&local_c,this->_Myhead,this);
  const_iterator::const_iterator(&local_14,this->_Myhead->_Left,this);
  cVar1._Ptr = (_Node *)local_14._padding_;
  cVar1._padding_ = (int)&local_14;
  cVar2._Ptr = (_Node *)local_c._padding_;
  cVar2._padding_ = (int)local_14._Ptr;
  erase(this,cVar1,cVar2);
  operator_delete(this->_Myhead);
  this->_Myhead = (_Node *)0x0;
  this->_Mysize = 0;
  return;
}
