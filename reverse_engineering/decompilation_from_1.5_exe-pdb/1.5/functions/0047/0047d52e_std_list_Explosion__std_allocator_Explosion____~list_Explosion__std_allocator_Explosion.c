/*
 * Entry: 0047d52e
 * Name: std::list<Explosion_*,std::allocator<Explosion_*>_>::~list<Explosion_*,std::allocator<Explosion_*>_>
 * Namespace: std::list<Explosion_*,std::allocator<Explosion_*>_>
 * Signature: void ~list<Explosion_*,std::allocator<Explosion_*>_>(list<Explosion_*,std::allocator<Explosion_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<Explosion_*,std::allocator<Explosion_*>_>::~list<Explosion_*,std::allocator<Explosion_*>_>
          (list<Explosion_*,std::allocator<Explosion_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
