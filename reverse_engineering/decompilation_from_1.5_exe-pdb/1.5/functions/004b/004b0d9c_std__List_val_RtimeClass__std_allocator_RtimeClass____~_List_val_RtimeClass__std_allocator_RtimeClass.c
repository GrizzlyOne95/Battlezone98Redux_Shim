/*
 * Entry: 004b0d9c
 * Name: std::_List_val<RtimeClass_*,std::allocator<RtimeClass_*>_>::~_List_val<RtimeClass_*,std::allocator<RtimeClass_*>_>
 * Namespace: std::_List_val<RtimeClass_*,std::allocator<RtimeClass_*>_>
 * Signature: void ~_List_val<RtimeClass_*,std::allocator<RtimeClass_*>_>(_List_val<RtimeClass_*,std::allocator<RtimeClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_val<RtimeClass_*,std::allocator<RtimeClass_*>_>::
~_List_val<RtimeClass_*,std::allocator<RtimeClass_*>_>
          (_List_val<RtimeClass_*,std::allocator<RtimeClass_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
