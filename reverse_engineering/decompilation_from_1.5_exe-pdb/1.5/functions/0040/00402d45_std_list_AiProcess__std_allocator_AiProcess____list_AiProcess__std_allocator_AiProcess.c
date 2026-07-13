/*
 * Entry: 00402d45
 * Name: std::list<AiProcess_*,std::allocator<AiProcess_*>_>::list<AiProcess_*,std::allocator<AiProcess_*>_>
 * Namespace: std::list<AiProcess_*,std::allocator<AiProcess_*>_>
 * Signature: list<AiProcess_*,std::allocator<AiProcess_*>_> * list<AiProcess_*,std::allocator<AiProcess_*>_>(list<AiProcess_*,std::allocator<AiProcess_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

list<AiProcess_*,std::allocator<AiProcess_*>_> * __thiscall
std::list<AiProcess_*,std::allocator<AiProcess_*>_>::list<AiProcess_*,std::allocator<AiProcess_*>_>
          (list<AiProcess_*,std::allocator<AiProcess_*>_> *this)

{
  _Node *p_Var1;
  
  _List_val<AiProcess_*,std::allocator<AiProcess_*>_>::
  _List_val<AiProcess_*,std::allocator<AiProcess_*>_>
            ((_List_val<AiProcess_*,std::allocator<AiProcess_*>_> *)this,SUB41(this,0));
  p_Var1 = _Buynode(this);
  this->_Mysize = 0;
  this->_Myhead = p_Var1;
  return this;
}
