/*
 * Entry: 0047f442
 * Name: std::allocator<Attachment_*>::deallocate
 * Namespace: std::allocator<Attachment_*>
 * Signature: void deallocate(allocator<Attachment_*> * this, Attachment * * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<Attachment_*>::deallocate
          (allocator<Attachment_*> *this,Attachment **param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
