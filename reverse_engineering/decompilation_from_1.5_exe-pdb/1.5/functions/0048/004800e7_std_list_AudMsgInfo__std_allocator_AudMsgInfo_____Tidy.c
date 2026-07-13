/*
 * Entry: 004800e7
 * Name: std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Tidy
 * Namespace: std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>
 * Signature: void _Tidy(list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::_Tidy
          (list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_> *this)

{
  clear(this);
  operator_delete(this->_Myhead);
  this->_Myhead = (_Node *)0x0;
  return;
}
