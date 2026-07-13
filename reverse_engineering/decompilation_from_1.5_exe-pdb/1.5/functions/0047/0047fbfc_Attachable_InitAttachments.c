/*
 * Entry: 0047fbfc
 * Name: Attachable::InitAttachments
 * Namespace: Attachable
 * Signature: void InitAttachments(Attachable * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Attachable::InitAttachments(Attachable *this,int param_1)

{
  Attachment **ppAVar1;
  uint uVar2;
  
  this->attachCount = param_1;
  std::vector<Attachment_*,std::allocator<Attachment_*>_>::resize
            (&this->attachments,param_1,(Attachment *)0x0);
  uVar2 = 0;
  if (0 < this->attachCount) {
    do {
      ppAVar1 = std::vector<Attachment_*,std::allocator<Attachment_*>_>::operator[]
                          (&this->attachments,uVar2);
      *ppAVar1 = (Attachment *)0x0;
      uVar2 = uVar2 + 1;
    } while ((int)uVar2 < this->attachCount);
  }
  return;
}
