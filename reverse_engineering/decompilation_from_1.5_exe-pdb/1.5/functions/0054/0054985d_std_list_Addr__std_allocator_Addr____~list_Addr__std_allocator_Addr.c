/*
 * Entry: 0054985d
 * Name: std::list<Addr_*,std::allocator<Addr_*>_>::~list<Addr_*,std::allocator<Addr_*>_>
 * Namespace: std::list<Addr_*,std::allocator<Addr_*>_>
 * Signature: void ~list<Addr_*,std::allocator<Addr_*>_>(list<Addr_*,std::allocator<Addr_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<Addr_*,std::allocator<Addr_*>_>::~list<Addr_*,std::allocator<Addr_*>_>
          (list<Addr_*,std::allocator<Addr_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
