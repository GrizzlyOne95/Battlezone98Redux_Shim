/*
 * Entry: 00402d12
 * Name: std::list<AiPath_*,std::allocator<AiPath_*>_>::list<AiPath_*,std::allocator<AiPath_*>_>
 * Namespace: std::list<AiPath_*,std::allocator<AiPath_*>_>
 * Signature: list<AiPath_*,std::allocator<AiPath_*>_> * list<AiPath_*,std::allocator<AiPath_*>_>(list<AiPath_*,std::allocator<AiPath_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

list<AiPath_*,std::allocator<AiPath_*>_> * __thiscall
std::list<AiPath_*,std::allocator<AiPath_*>_>::list<AiPath_*,std::allocator<AiPath_*>_>
          (list<AiPath_*,std::allocator<AiPath_*>_> *this)

{
  _Node *p_Var1;
  
  _List_val<AiPath_*,std::allocator<AiPath_*>_>::_List_val<AiPath_*,std::allocator<AiPath_*>_>
            ((_List_val<AiPath_*,std::allocator<AiPath_*>_> *)this,SUB41(this,0));
  p_Var1 = _Buynode(this);
  this->_Mysize = 0;
  this->_Myhead = p_Var1;
  return this;
}
