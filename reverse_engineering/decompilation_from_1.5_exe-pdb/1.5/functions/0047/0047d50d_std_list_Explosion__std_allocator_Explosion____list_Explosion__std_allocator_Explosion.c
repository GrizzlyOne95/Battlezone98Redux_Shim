/*
 * Entry: 0047d50d
 * Name: std::list<Explosion_*,std::allocator<Explosion_*>_>::list<Explosion_*,std::allocator<Explosion_*>_>
 * Namespace: std::list<Explosion_*,std::allocator<Explosion_*>_>
 * Signature: list<Explosion_*,std::allocator<Explosion_*>_> * list<Explosion_*,std::allocator<Explosion_*>_>(list<Explosion_*,std::allocator<Explosion_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

list<Explosion_*,std::allocator<Explosion_*>_> * __thiscall
std::list<Explosion_*,std::allocator<Explosion_*>_>::list<Explosion_*,std::allocator<Explosion_*>_>
          (list<Explosion_*,std::allocator<Explosion_*>_> *this)

{
  _Node *p_Var1;
  
  _List_val<Explosion_*,std::allocator<Explosion_*>_>::
  _List_val<Explosion_*,std::allocator<Explosion_*>_>
            ((_List_val<Explosion_*,std::allocator<Explosion_*>_> *)this,SUB41(this,0));
  p_Var1 = _Buynode(this);
  this->_Mysize = 0;
  this->_Myhead = p_Var1;
  return this;
}
