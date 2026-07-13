/*
 * Entry: 00402617
 * Name: std::_List_ptr<AOI_*,std::allocator<AOI_*>_>::~_List_ptr<AOI_*,std::allocator<AOI_*>_>
 * Namespace: std::_List_ptr<AOI_*,std::allocator<AOI_*>_>
 * Signature: void ~_List_ptr<AOI_*,std::allocator<AOI_*>_>(_List_ptr<AOI_*,std::allocator<AOI_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_ptr<AOI_*,std::allocator<AOI_*>_>::~_List_ptr<AOI_*,std::allocator<AOI_*>_>
          (_List_ptr<AOI_*,std::allocator<AOI_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
