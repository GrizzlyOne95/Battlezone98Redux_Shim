/*
 * Entry: 00408a46
 * Name: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::_Lrotate
 * Namespace: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
 * Signature: void _Lrotate(_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_> * this, _Node * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::
_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
::_Lrotate(_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
           *this,_Node *param_1)

{
  _Node *p_Var1;
  _Node *p_Var2;
  
  p_Var1 = param_1->_Right;
  param_1->_Right = p_Var1->_Left;
  if (p_Var1->_Left->_Isnil == '\0') {
    p_Var1->_Left->_Parent = param_1;
  }
  p_Var1->_Parent = param_1->_Parent;
  if (param_1 == this->_Myhead->_Parent) {
    this->_Myhead->_Parent = p_Var1;
  }
  else {
    p_Var2 = param_1->_Parent;
    if (param_1 == p_Var2->_Left) {
      p_Var2->_Left = p_Var1;
    }
    else {
      p_Var2->_Right = p_Var1;
    }
  }
  p_Var1->_Left = param_1;
  param_1->_Parent = p_Var1;
  return;
}
