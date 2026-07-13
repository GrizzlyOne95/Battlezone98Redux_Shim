/*
 * Entry: 0048da3f
 * Name: std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
 * Namespace: std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
 * Signature: list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_> * list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>(list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_> * this, allocator<std::pair<unsigned_long_const_,unsigned_long>_> * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
* __thiscall
std::
list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
::
list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
          (list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
           *this,allocator<std::pair<unsigned_long_const_,unsigned_long>_> *param_1)

{
  _Node *p_Var1;
  
  _List_val<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
  ::
  _List_val<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
            ((_List_val<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
              *)this,SUB41(this,0));
  p_Var1 = _Buynode(this);
  this->_Mysize = 0;
  this->_Myhead = p_Var1;
  return this;
}
