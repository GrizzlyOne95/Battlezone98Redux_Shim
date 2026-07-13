/*
 * Entry: 00408b01
 * Name: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::iterator::operator--
 * Namespace: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::iterator
 * Signature: iterator * operator--(iterator * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

iterator * __thiscall
std::
_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
::iterator::operator--(iterator *this)

{
  const_iterator::_Dec((const_iterator *)this);
  return this;
}
