/*
 * Entry: 005332dc
 * Name: std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::_Rrotate
 * Namespace: std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
 * Signature: void _Rrotate(_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_> * this, _Node * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::
_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
::_Rrotate(_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
           *this,_Node *param_1)

{
  _Node *p_Var1;
  _Node *p_Var2;
  
  p_Var1 = param_1->_Left;
  param_1->_Left = p_Var1->_Right;
  if (p_Var1->_Right->_Isnil == '\0') {
    p_Var1->_Right->_Parent = param_1;
  }
  p_Var1->_Parent = param_1->_Parent;
  if (param_1 == this->_Myhead->_Parent) {
    this->_Myhead->_Parent = p_Var1;
  }
  else {
    p_Var2 = param_1->_Parent;
    if (param_1 == p_Var2->_Right) {
      p_Var2->_Right = p_Var1;
    }
    else {
      p_Var2->_Left = p_Var1;
    }
  }
  p_Var1->_Right = param_1;
  param_1->_Parent = p_Var1;
  return;
}
