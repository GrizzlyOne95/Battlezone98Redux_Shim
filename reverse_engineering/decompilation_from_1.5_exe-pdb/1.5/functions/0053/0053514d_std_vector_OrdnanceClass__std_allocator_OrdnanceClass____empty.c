/*
 * Entry: 0053514d
 * Name: std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::empty
 * Namespace: std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
 * Signature: bool empty(vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::empty
          (vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> *this)

{
  return (bool)('\x01' - (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffffcU) != 0));
}
