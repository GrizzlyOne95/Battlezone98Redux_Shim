/*
 * Entry: 0047f8d3
 * Name: Attachable::~Attachable
 * Namespace: Attachable
 * Signature: void ~Attachable(Attachable * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Attachable::~Attachable(Attachable *this)

{
  Attachment **ppAVar1;
  uint uVar2;
  
  uVar2 = 0;
  this->_padding_ = (int)&_vftable_;
  if (0 < this->attachCount) {
    do {
      ppAVar1 = std::vector<Attachment_*,std::allocator<Attachment_*>_>::operator[]
                          (&this->attachments,uVar2);
      if (*ppAVar1 != (Attachment *)0x0) {
        (**(code **)**ppAVar1)(1);
      }
      uVar2 = uVar2 + 1;
    } while ((int)uVar2 < this->attachCount);
  }
  std::vector<Attachment_*,std::allocator<Attachment_*>_>::_Tidy(&this->attachments);
  operator_delete((void *)(this->attachments)._padding_);
  return;
}
