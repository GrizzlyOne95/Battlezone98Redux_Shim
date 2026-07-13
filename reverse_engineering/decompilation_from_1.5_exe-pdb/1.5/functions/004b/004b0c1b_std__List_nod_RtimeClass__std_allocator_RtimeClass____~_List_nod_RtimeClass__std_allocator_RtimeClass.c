/*
 * Entry: 004b0c1b
 * Name: std::_List_nod<RtimeClass_*,std::allocator<RtimeClass_*>_>::~_List_nod<RtimeClass_*,std::allocator<RtimeClass_*>_>
 * Namespace: std::_List_nod<RtimeClass_*,std::allocator<RtimeClass_*>_>
 * Signature: void ~_List_nod<RtimeClass_*,std::allocator<RtimeClass_*>_>(_List_nod<RtimeClass_*,std::allocator<RtimeClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_nod<RtimeClass_*,std::allocator<RtimeClass_*>_>::
~_List_nod<RtimeClass_*,std::allocator<RtimeClass_*>_>
          (_List_nod<RtimeClass_*,std::allocator<RtimeClass_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
