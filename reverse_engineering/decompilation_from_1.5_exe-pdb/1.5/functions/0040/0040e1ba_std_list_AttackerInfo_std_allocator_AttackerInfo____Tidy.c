/*
 * Entry: 0040e1ba
 * Name: std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Tidy
 * Namespace: std::list<AttackerInfo,std::allocator<AttackerInfo>_>
 * Signature: void _Tidy(list<AttackerInfo,std::allocator<AttackerInfo>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<AttackerInfo,std::allocator<AttackerInfo>_>::_Tidy
          (list<AttackerInfo,std::allocator<AttackerInfo>_> *this)

{
  clear(this);
  operator_delete(this->_Myhead);
  this->_Myhead = (_Node *)0x0;
  return;
}
