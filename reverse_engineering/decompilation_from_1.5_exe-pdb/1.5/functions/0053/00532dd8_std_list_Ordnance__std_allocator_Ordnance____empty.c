/*
 * Entry: 00532dd8
 * Name: std::list<Ordnance_*,std::allocator<Ordnance_*>_>::empty
 * Namespace: std::list<Ordnance_*,std::allocator<Ordnance_*>_>
 * Signature: bool empty(list<Ordnance_*,std::allocator<Ordnance_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::list<Ordnance_*,std::allocator<Ordnance_*>_>::empty
          (list<Ordnance_*,std::allocator<Ordnance_*>_> *this)

{
  return this->_Mysize == 0;
}
