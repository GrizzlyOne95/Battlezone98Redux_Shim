/*
 * Entry: 00533265
 * Name: std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::_Lbound
 * Namespace: std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
 * Signature: _Node * _Lbound(_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_> * this, pair<unsigned_short,unsigned_short> * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __thiscall
std::
_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
::_Lbound(_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
          *this,pair<unsigned_short,unsigned_short> *param_1)

{
  _Node *p_Var1;
  bool bVar2;
  _Node *p_Var3;
  _Node *p_Var4;
  
  p_Var1 = this->_Myhead->_Parent;
  p_Var4 = this->_Myhead;
  while (p_Var3 = p_Var1, p_Var3->_Isnil == '\0') {
    bVar2 = operator<<unsigned_short,unsigned_short>(&(p_Var3->_Myval).first,param_1);
    if (bVar2) {
      p_Var1 = p_Var3->_Right;
    }
    else {
      p_Var1 = p_Var3->_Left;
      p_Var4 = p_Var3;
    }
  }
  return p_Var4;
}
