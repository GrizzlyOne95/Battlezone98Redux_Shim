/*
 * Entry: 004c7fd7
 * Name: std::_List_ptr<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::~_List_ptr<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>
 * Namespace: std::_List_ptr<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>
 * Signature: void ~_List_ptr<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>(_List_ptr<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_ptr<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::
~_List_ptr<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>
          (_List_ptr<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
