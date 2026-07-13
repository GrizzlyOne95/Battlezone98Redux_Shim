/*
 * Entry: 004e11f0
 * Name: std::_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>::iterator::operator--
 * Namespace: std::_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>::iterator
 * Signature: iterator * operator--(iterator * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

iterator * __thiscall
std::
_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
::iterator::operator--(iterator *this)

{
  const_iterator::_Dec((const_iterator *)this);
  return this;
}
