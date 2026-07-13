/*
 * Entry: 004026d4
 * Name: std::list<AOI_*,std::allocator<AOI_*>_>::_Tidy
 * Namespace: std::list<AOI_*,std::allocator<AOI_*>_>
 * Signature: void _Tidy(list<AOI_*,std::allocator<AOI_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<AOI_*,std::allocator<AOI_*>_>::_Tidy(list<AOI_*,std::allocator<AOI_*>_> *this)

{
  clear(this);
  operator_delete(this->_Myhead);
  this->_Myhead = (_Node *)0x0;
  return;
}
