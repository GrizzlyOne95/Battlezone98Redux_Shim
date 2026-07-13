/*
 * Entry: 0053077f
 * Name: ImageRefract::~ImageRefract
 * Namespace: ImageRefract
 * Signature: void ~ImageRefract(ImageRefract * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ImageRefract::~ImageRefract(ImageRefract *this)

{
  *(undefined ***)this = &_vftable_;
  if ((*(uint *)(*(int *)&this->field_0x18 + 0x14) >> 10 & 1) != 0) {
    Deactivate(this);
  }
  SpecialItem::~SpecialItem((SpecialItem *)this);
  return;
}
