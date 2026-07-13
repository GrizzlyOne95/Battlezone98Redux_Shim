/*
 * Entry: 00408b0d
 * Name: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::const_iterator::operator++
 * Namespace: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::const_iterator
 * Signature: const_iterator operator++(const_iterator * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

const_iterator __thiscall
std::
_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
::const_iterator::operator++(const_iterator *this,int param_1)

{
  _Node *extraout_EDX;
  const_iterator cVar1;
  
  *(int *)param_1 = this->_padding_;
  *(_Node **)(param_1 + 4) = this->_Ptr;
  _Inc(this);
  cVar1._Ptr = extraout_EDX;
  cVar1._padding_ = param_1;
  return cVar1;
}
