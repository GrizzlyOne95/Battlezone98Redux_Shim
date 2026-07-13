/*
 * Entry: 0040b12a
 * Name: std::list<AOI_*,std::allocator<AOI_*>_>::empty
 * Namespace: std::list<AOI_*,std::allocator<AOI_*>_>
 * Signature: bool empty(list<AOI_*,std::allocator<AOI_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::list<AOI_*,std::allocator<AOI_*>_>::empty(list<AOI_*,std::allocator<AOI_*>_> *this)

{
  return this->_Mysize == 0;
}
