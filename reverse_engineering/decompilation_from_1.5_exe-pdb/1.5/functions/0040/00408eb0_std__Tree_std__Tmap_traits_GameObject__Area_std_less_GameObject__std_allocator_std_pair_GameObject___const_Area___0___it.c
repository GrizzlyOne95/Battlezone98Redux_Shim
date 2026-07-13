/*
 * Entry: 00408eb0
 * Name: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::iterator::iterator
 * Namespace: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::iterator
 * Signature: iterator * iterator(iterator * this, _Node * param_1, _Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_> * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

iterator * __thiscall
std::
_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
::iterator::iterator
          (iterator *this,_Node *param_1,
          _Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
          *param_2)

{
  const_iterator::const_iterator((const_iterator *)this,param_1,param_2);
  return this;
}
