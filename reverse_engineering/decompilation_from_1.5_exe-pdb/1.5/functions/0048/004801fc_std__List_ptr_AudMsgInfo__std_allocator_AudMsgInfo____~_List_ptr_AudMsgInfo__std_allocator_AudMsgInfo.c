/*
 * Entry: 004801fc
 * Name: std::_List_ptr<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::~_List_ptr<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>
 * Namespace: std::_List_ptr<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>
 * Signature: void ~_List_ptr<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>(_List_ptr<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_List_ptr<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::
~_List_ptr<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>
          (_List_ptr<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
