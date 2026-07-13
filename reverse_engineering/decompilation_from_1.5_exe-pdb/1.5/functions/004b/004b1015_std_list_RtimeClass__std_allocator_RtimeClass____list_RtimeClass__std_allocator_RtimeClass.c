/*
 * Entry: 004b1015
 * Name: std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::list<RtimeClass_*,std::allocator<RtimeClass_*>_>
 * Namespace: std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>
 * Signature: list<RtimeClass_*,std::allocator<RtimeClass_*>_> * list<RtimeClass_*,std::allocator<RtimeClass_*>_>(list<RtimeClass_*,std::allocator<RtimeClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

list<RtimeClass_*,std::allocator<RtimeClass_*>_> * __thiscall
std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::
list<RtimeClass_*,std::allocator<RtimeClass_*>_>
          (list<RtimeClass_*,std::allocator<RtimeClass_*>_> *this)

{
  _Node *p_Var1;
  
  _List_val<RtimeClass_*,std::allocator<RtimeClass_*>_>::
  _List_val<RtimeClass_*,std::allocator<RtimeClass_*>_>
            ((_List_val<RtimeClass_*,std::allocator<RtimeClass_*>_> *)this,SUB41(this,0));
  p_Var1 = _Buynode(this);
  this->_Mysize = 0;
  this->_Myhead = p_Var1;
  return this;
}
