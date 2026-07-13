/*
 * Entry: 0047c9a8
 * Name: std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::const_iterator::operator++
 * Namespace: std::_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>::const_iterator
 * Signature: const_iterator * operator++(const_iterator * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

const_iterator * __thiscall
std::
_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
::const_iterator::operator++(const_iterator *this)

{
  _Inc(this);
  return this;
}
