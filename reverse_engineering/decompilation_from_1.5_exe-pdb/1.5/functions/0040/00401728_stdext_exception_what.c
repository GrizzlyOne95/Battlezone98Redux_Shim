/*
 * Entry: 00401728
 * Name: stdext::exception::what
 * Namespace: stdext::exception
 * Signature: char * what(exception * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __thiscall stdext::exception::what(exception *this)

{
  char *pcVar1;
  
  pcVar1 = this->_Ptr;
  if (pcVar1 == (char *)0x0) {
    pcVar1 = "unknown exception";
  }
  return pcVar1;
}
