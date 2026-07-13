/*
 * Entry: 004806be
 * Name: std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>
 * Namespace: std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>
 * Signature: list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_> * list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>(list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_> * __thiscall
std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::
list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>
          (list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_> *this)

{
  _Node *p_Var1;
  
  _List_val<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::
  _List_val<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>
            ((_List_val<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_> *)this,SUB41(this,0));
  p_Var1 = _Buynode(this);
  this->_Mysize = 0;
  this->_Myhead = p_Var1;
  return this;
}
