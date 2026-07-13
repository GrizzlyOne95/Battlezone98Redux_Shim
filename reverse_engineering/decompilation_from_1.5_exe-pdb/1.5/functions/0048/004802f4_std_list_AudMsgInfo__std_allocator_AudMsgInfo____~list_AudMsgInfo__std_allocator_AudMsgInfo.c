/*
 * Entry: 004802f4
 * Name: std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::~list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>
 * Namespace: std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>
 * Signature: void ~list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>(list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::
~list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>
          (list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
