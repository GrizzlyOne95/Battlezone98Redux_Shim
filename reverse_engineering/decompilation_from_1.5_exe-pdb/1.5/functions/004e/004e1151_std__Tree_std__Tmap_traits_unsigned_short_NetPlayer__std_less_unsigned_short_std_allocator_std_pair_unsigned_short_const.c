/*
 * Entry: 004e1151
 * Name: std::_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>::_Lbound
 * Namespace: std::_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
 * Signature: _Node * _Lbound(_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_> * this, ushort * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __thiscall
std::
_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
::_Lbound(_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
          *this,ushort *param_1)

{
  _Node *p_Var1;
  _Node *p_Var2;
  _Node *p_Var3;
  
  p_Var2 = this->_Myhead;
  if (p_Var2->_Parent->_Isnil == '\0') {
    p_Var1 = p_Var2;
    p_Var3 = p_Var2->_Parent;
    do {
      p_Var2 = p_Var3;
      if ((p_Var2->_Myval).first < *param_1) {
        p_Var3 = p_Var2->_Right;
        p_Var2 = p_Var1;
      }
      else {
        p_Var3 = p_Var2->_Left;
      }
      p_Var1 = p_Var2;
    } while (p_Var3->_Isnil == '\0');
  }
  return p_Var2;
}
