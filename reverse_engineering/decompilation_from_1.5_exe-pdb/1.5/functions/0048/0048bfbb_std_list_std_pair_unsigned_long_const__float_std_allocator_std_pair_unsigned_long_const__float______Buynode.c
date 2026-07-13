/*
 * Entry: 0048bfbb
 * Name: std::list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>::_Buynode
 * Namespace: std::list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
 * Signature: _Node * _Buynode(list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_> * this, _Node * param_1, _Node * param_2, pair<unsigned_long_const_,float> * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __thiscall
std::
list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
::_Buynode(list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
           *this,_Node *param_1,_Node *param_2,pair<unsigned_long_const_,float> *param_3)

{
  _Node *p_Var1;
  
  p_Var1 = _Allocate<std::_List_nod<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>::_Node>
                     (1,(_Node *)0x0);
  if (p_Var1 != (_Node *)0x0) {
    p_Var1->_Next = param_1;
  }
  if (&p_Var1->_Prev != (_Node **)0x0) {
    p_Var1->_Prev = param_2;
  }
  _Construct<std::pair<unsigned_long_const_,float>,std::pair<unsigned_long_const_,float>_>
            (&p_Var1->_Myval,param_3);
  return p_Var1;
}
