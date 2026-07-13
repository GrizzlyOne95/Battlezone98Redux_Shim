/*
 * Entry: 00557d03
 * Name: std::vector<Session_*,std::allocator<Session_*>_>::_Tidy
 * Namespace: std::vector<Session_*,std::allocator<Session_*>_>
 * Signature: void _Tidy(vector<Session_*,std::allocator<Session_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Session_*,std::allocator<Session_*>_>::_Tidy
          (vector<Session_*,std::allocator<Session_*>_> *this)

{
  if (this->_Myfirst != (Session **)0x0) {
    operator_delete(this->_Myfirst);
  }
  this->_Myfirst = (Session **)0x0;
  this->_Mylast = (Session **)0x0;
  this->_Myend = (Session **)0x0;
  return;
}
