/*
 * Entry: 00402d99
 * Name: std::list<AOI_*,std::allocator<AOI_*>_>::~list<AOI_*,std::allocator<AOI_*>_>
 * Namespace: std::list<AOI_*,std::allocator<AOI_*>_>
 * Signature: void ~list<AOI_*,std::allocator<AOI_*>_>(list<AOI_*,std::allocator<AOI_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<AOI_*,std::allocator<AOI_*>_>::~list<AOI_*,std::allocator<AOI_*>_>
          (list<AOI_*,std::allocator<AOI_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
