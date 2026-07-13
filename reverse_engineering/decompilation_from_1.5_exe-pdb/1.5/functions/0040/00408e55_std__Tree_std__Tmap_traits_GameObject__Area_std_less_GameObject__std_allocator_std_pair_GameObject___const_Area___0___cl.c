/*
 * Entry: 00408e55
 * Name: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::clear
 * Namespace: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
 * Signature: void clear(_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::
_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
::clear(_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
        *this)

{
  _Node **pp_Var1;
  
  pp_Var1 = &this->_Myhead;
  _Erase(this,(*pp_Var1)->_Parent);
  (*pp_Var1)->_Parent = *pp_Var1;
  this->_Mysize = 0;
  (*pp_Var1)->_Left = *pp_Var1;
  (*pp_Var1)->_Right = *pp_Var1;
  return;
}
