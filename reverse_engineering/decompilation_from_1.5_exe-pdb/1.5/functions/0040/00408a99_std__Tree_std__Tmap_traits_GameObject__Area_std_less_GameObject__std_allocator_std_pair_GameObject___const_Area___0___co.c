/*
 * Entry: 00408a99
 * Name: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::const_iterator::operator++
 * Namespace: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::const_iterator
 * Signature: const_iterator * operator++(const_iterator * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

const_iterator * __thiscall
std::
_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
::const_iterator::operator++(const_iterator *this)

{
  _Inc(this);
  return this;
}
