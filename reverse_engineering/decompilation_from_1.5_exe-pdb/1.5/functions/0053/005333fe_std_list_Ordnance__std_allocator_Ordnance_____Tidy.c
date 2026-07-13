/*
 * Entry: 005333fe
 * Name: std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Tidy
 * Namespace: std::list<Ordnance_*,std::allocator<Ordnance_*>_>
 * Signature: void _Tidy(list<Ordnance_*,std::allocator<Ordnance_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Tidy
          (list<Ordnance_*,std::allocator<Ordnance_*>_> *this)

{
  clear(this);
  operator_delete(this->_Myhead);
  this->_Myhead = (_Node *)0x0;
  return;
}
