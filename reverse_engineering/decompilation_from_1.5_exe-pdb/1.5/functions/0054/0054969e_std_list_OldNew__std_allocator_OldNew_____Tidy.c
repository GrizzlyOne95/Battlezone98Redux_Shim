/*
 * Entry: 0054969e
 * Name: std::list<OldNew_*,std::allocator<OldNew_*>_>::_Tidy
 * Namespace: std::list<OldNew_*,std::allocator<OldNew_*>_>
 * Signature: void _Tidy(list<OldNew_*,std::allocator<OldNew_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<OldNew_*,std::allocator<OldNew_*>_>::_Tidy(list<OldNew_*,std::allocator<OldNew_*>_> *this)

{
  clear(this);
  operator_delete(this->_Myhead);
  this->_Myhead = (_Node *)0x0;
  return;
}
