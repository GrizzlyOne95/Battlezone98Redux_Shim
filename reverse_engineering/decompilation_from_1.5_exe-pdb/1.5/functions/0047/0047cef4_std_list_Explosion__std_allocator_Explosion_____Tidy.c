/*
 * Entry: 0047cef4
 * Name: std::list<Explosion_*,std::allocator<Explosion_*>_>::_Tidy
 * Namespace: std::list<Explosion_*,std::allocator<Explosion_*>_>
 * Signature: void _Tidy(list<Explosion_*,std::allocator<Explosion_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<Explosion_*,std::allocator<Explosion_*>_>::_Tidy
          (list<Explosion_*,std::allocator<Explosion_*>_> *this)

{
  clear(this);
  operator_delete(this->_Myhead);
  this->_Myhead = (_Node *)0x0;
  return;
}
