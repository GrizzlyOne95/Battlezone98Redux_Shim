/*
 * Entry: 004adf03
 * Name: std::vector<Scanner_*,std::allocator<Scanner_*>_>::_Tidy
 * Namespace: std::vector<Scanner_*,std::allocator<Scanner_*>_>
 * Signature: void _Tidy(vector<Scanner_*,std::allocator<Scanner_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Scanner_*,std::allocator<Scanner_*>_>::_Tidy
          (vector<Scanner_*,std::allocator<Scanner_*>_> *this)

{
  if (this->_Myfirst != (Scanner **)0x0) {
    operator_delete(this->_Myfirst);
  }
  this->_Myfirst = (Scanner **)0x0;
  this->_Mylast = (Scanner **)0x0;
  this->_Myend = (Scanner **)0x0;
  return;
}
