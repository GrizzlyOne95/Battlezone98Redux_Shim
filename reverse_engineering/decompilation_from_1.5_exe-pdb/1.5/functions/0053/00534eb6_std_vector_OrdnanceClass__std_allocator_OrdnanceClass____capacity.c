/*
 * Entry: 00534eb6
 * Name: std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::capacity
 * Namespace: std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
 * Signature: uint capacity(vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::capacity
          (vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> *this)

{
  if (this->_Myfirst == (OrdnanceClass **)0x0) {
    return 0;
  }
  return (int)this->_Myend - (int)this->_Myfirst >> 2;
}
