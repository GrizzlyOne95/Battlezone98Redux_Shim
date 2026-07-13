/*
 * Entry: 0052dc26
 * Name: std::list<Explosion_*,std::allocator<Explosion_*>_>::empty
 * Namespace: std::list<Explosion_*,std::allocator<Explosion_*>_>
 * Signature: bool empty(list<Explosion_*,std::allocator<Explosion_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::list<Explosion_*,std::allocator<Explosion_*>_>::empty
          (list<Explosion_*,std::allocator<Explosion_*>_> *this)

{
  return this->_Mysize == 0;
}
