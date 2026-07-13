/*
 * Entry: 00402dab
 * Name: std::list<AiMissionClass_*,std::allocator<AiMissionClass_*>_>::list<AiMissionClass_*,std::allocator<AiMissionClass_*>_>
 * Namespace: std::list<AiMissionClass_*,std::allocator<AiMissionClass_*>_>
 * Signature: list<AiMissionClass_*,std::allocator<AiMissionClass_*>_> * list<AiMissionClass_*,std::allocator<AiMissionClass_*>_>(list<AiMissionClass_*,std::allocator<AiMissionClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

list<AiMissionClass_*,std::allocator<AiMissionClass_*>_> * __thiscall
std::list<AiMissionClass_*,std::allocator<AiMissionClass_*>_>::
list<AiMissionClass_*,std::allocator<AiMissionClass_*>_>
          (list<AiMissionClass_*,std::allocator<AiMissionClass_*>_> *this)

{
  _Node *p_Var1;
  
  _List_val<AiMissionClass_*,std::allocator<AiMissionClass_*>_>::
  _List_val<AiMissionClass_*,std::allocator<AiMissionClass_*>_>
            ((_List_val<AiMissionClass_*,std::allocator<AiMissionClass_*>_> *)this,SUB41(this,0));
  p_Var1 = _Buynode(this);
  this->_Mysize = 0;
  this->_Myhead = p_Var1;
  return this;
}
