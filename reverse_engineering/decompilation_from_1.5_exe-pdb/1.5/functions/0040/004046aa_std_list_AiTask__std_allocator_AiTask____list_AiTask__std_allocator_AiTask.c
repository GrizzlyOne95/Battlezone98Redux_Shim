/*
 * Entry: 004046aa
 * Name: std::list<AiTask_*,std::allocator<AiTask_*>_>::list<AiTask_*,std::allocator<AiTask_*>_>
 * Namespace: std::list<AiTask_*,std::allocator<AiTask_*>_>
 * Signature: list<AiTask_*,std::allocator<AiTask_*>_> * list<AiTask_*,std::allocator<AiTask_*>_>(list<AiTask_*,std::allocator<AiTask_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

list<AiTask_*,std::allocator<AiTask_*>_> * __thiscall
std::list<AiTask_*,std::allocator<AiTask_*>_>::list<AiTask_*,std::allocator<AiTask_*>_>
          (list<AiTask_*,std::allocator<AiTask_*>_> *this)

{
  _Node *p_Var1;
  
  _List_val<AiTask_*,std::allocator<AiTask_*>_>::_List_val<AiTask_*,std::allocator<AiTask_*>_>
            ((_List_val<AiTask_*,std::allocator<AiTask_*>_> *)this,SUB41(this,0));
  p_Var1 = _Buynode(this);
  this->_Mysize = 0;
  this->_Myhead = p_Var1;
  return this;
}
