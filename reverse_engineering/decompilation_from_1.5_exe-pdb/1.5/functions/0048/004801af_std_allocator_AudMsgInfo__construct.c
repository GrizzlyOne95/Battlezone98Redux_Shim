/*
 * Entry: 004801af
 * Name: std::allocator<AudMsgInfo_*>::construct
 * Namespace: std::allocator<AudMsgInfo_*>
 * Signature: void construct(allocator<AudMsgInfo_*> * this, AudMsgInfo * * param_1, AudMsgInfo * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<AudMsgInfo_*>::construct
          (allocator<AudMsgInfo_*> *this,AudMsgInfo **param_1,AudMsgInfo **param_2)

{
  if (param_1 != (AudMsgInfo **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
