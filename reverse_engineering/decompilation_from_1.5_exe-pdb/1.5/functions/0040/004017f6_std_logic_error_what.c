/*
 * Entry: 004017f6
 * Name: std::logic_error::what
 * Namespace: std::logic_error
 * Signature: char * what(logic_error * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __thiscall std::logic_error::what(logic_error *this)

{
  if (0xf < (this->_Str)._Myres) {
    return (this->_Str)._Bx._Ptr;
  }
  return (char *)&(this->_Str)._Bx;
}
