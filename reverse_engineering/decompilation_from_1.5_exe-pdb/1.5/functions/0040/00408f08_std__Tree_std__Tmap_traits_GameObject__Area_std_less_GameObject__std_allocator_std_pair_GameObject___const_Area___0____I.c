/*
 * Entry: 00408f08
 * Name: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::_Init
 * Namespace: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
 * Signature: void _Init(_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::
_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
::_Init(_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
        *this)

{
  _Node **pp_Var1;
  _Node *p_Var2;
  
  p_Var2 = _Buynode(this);
  pp_Var1 = &this->_Myhead;
  *pp_Var1 = p_Var2;
  p_Var2->_Isnil = '\x01';
  (*pp_Var1)->_Parent = *pp_Var1;
  (*pp_Var1)->_Left = *pp_Var1;
  (*pp_Var1)->_Right = *pp_Var1;
  this->_Mysize = 0;
  return;
}
