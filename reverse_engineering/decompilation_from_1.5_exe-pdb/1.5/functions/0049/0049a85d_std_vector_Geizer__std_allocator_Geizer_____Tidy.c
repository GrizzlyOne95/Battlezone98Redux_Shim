/*
 * Entry: 0049a85d
 * Name: std::vector<Geizer_*,std::allocator<Geizer_*>_>::_Tidy
 * Namespace: std::vector<Geizer_*,std::allocator<Geizer_*>_>
 * Signature: void _Tidy(vector<Geizer_*,std::allocator<Geizer_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Geizer_*,std::allocator<Geizer_*>_>::_Tidy
          (vector<Geizer_*,std::allocator<Geizer_*>_> *this)

{
  if (this->_Myfirst != (Geizer **)0x0) {
    operator_delete(this->_Myfirst);
  }
  this->_Myfirst = (Geizer **)0x0;
  this->_Mylast = (Geizer **)0x0;
  this->_Myend = (Geizer **)0x0;
  return;
}
