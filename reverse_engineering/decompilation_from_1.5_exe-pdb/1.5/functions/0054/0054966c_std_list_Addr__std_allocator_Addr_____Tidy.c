/*
 * Entry: 0054966c
 * Name: std::list<Addr_*,std::allocator<Addr_*>_>::_Tidy
 * Namespace: std::list<Addr_*,std::allocator<Addr_*>_>
 * Signature: void _Tidy(list<Addr_*,std::allocator<Addr_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<Addr_*,std::allocator<Addr_*>_>::_Tidy(list<Addr_*,std::allocator<Addr_*>_> *this)

{
  clear(this);
  operator_delete(this->_Myhead);
  this->_Myhead = (_Node *)0x0;
  return;
}
