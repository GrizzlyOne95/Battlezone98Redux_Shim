/*
 * Entry: 005352d2
 * Name: std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::_Tidy
 * Namespace: std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
 * Signature: void _Tidy(vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::_Tidy
          (vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> *this)

{
  if (this->_Myfirst != (OrdnanceClass **)0x0) {
    operator_delete(this->_Myfirst);
  }
  this->_Myfirst = (OrdnanceClass **)0x0;
  this->_Mylast = (OrdnanceClass **)0x0;
  this->_Myend = (OrdnanceClass **)0x0;
  return;
}
