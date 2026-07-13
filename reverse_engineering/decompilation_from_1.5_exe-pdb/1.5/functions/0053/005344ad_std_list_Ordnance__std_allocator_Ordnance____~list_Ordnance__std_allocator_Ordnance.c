/*
 * Entry: 005344ad
 * Name: std::list<Ordnance_*,std::allocator<Ordnance_*>_>::~list<Ordnance_*,std::allocator<Ordnance_*>_>
 * Namespace: std::list<Ordnance_*,std::allocator<Ordnance_*>_>
 * Signature: void ~list<Ordnance_*,std::allocator<Ordnance_*>_>(list<Ordnance_*,std::allocator<Ordnance_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<Ordnance_*,std::allocator<Ordnance_*>_>::~list<Ordnance_*,std::allocator<Ordnance_*>_>
          (list<Ordnance_*,std::allocator<Ordnance_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
