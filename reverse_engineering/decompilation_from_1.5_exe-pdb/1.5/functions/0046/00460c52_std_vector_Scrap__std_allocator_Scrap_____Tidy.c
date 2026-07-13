/*
 * Entry: 00460c52
 * Name: std::vector<Scrap_*,std::allocator<Scrap_*>_>::_Tidy
 * Namespace: std::vector<Scrap_*,std::allocator<Scrap_*>_>
 * Signature: void _Tidy(vector<Scrap_*,std::allocator<Scrap_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Scrap_*,std::allocator<Scrap_*>_>::_Tidy(vector<Scrap_*,std::allocator<Scrap_*>_> *this)

{
  if (this->_Myfirst != (Scrap **)0x0) {
    operator_delete(this->_Myfirst);
  }
  this->_Myfirst = (Scrap **)0x0;
  this->_Mylast = (Scrap **)0x0;
  this->_Myend = (Scrap **)0x0;
  return;
}
