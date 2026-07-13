/*
 * Entry: 00535418
 * Name: std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::pop_back
 * Namespace: std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
 * Signature: void pop_back(vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::pop_back
          (vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> *this)

{
  if (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffffcU) != 0) {
    this->_Mylast = this->_Mylast + -1;
  }
  return;
}
