/*
 * Entry: 004b0d2c
 * Name: std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Buynode
 * Namespace: std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>
 * Signature: _Node * _Buynode(list<RtimeClass_*,std::allocator<RtimeClass_*>_> * this, _Node * param_1, _Node * param_2, RtimeClass * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Node * __thiscall
std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Buynode
          (list<RtimeClass_*,std::allocator<RtimeClass_*>_> *this,_Node *param_1,_Node *param_2,
          RtimeClass **param_3)

{
  _Node *p_Var1;
  
  p_Var1 = _Allocate<std::_List_nod<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Node>
                     (1,(_Node *)0x0);
  if (p_Var1 != (_Node *)0x0) {
    p_Var1->_Next = param_1;
  }
  if (&p_Var1->_Prev != (_Node **)0x0) {
    p_Var1->_Prev = param_2;
  }
  if (&p_Var1->_Myval != (RtimeClass **)0x0) {
    p_Var1->_Myval = *param_3;
  }
  return p_Var1;
}
