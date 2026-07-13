/*
 * Entry: 0047f712
 * Name: std::allocator<Attachment_*>::allocate
 * Namespace: std::allocator<Attachment_*>
 * Signature: Attachment * * allocate(allocator<Attachment_*> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Attachment ** __thiscall
std::allocator<Attachment_*>::allocate(allocator<Attachment_*> *this,uint param_1)

{
  Attachment **ppAVar1;
  
  ppAVar1 = _Allocate<Attachment_*>(param_1,(Attachment **)0x0);
  return ppAVar1;
}
