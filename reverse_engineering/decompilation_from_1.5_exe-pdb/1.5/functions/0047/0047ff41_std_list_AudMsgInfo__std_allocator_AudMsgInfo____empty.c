/*
 * Entry: 0047ff41
 * Name: std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::empty
 * Namespace: std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>
 * Signature: bool empty(list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::empty
          (list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_> *this)

{
  return this->_Mysize == 0;
}
