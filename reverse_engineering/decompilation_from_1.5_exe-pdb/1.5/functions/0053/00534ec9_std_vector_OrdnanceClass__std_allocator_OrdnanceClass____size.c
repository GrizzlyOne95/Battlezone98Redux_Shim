/*
 * Entry: 00534ec9
 * Name: std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::size
 * Namespace: std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
 * Signature: uint size(vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::size
          (vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> *this)

{
  return (int)this->_Mylast - (int)this->_Myfirst >> 2;
}
