/*
 * Entry: 00530652
 * Name: ImageRefractClass::ImageRefractClass
 * Namespace: ImageRefractClass
 * Signature: ImageRefractClass * ImageRefractClass(ImageRefractClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ImageRefractClass * __thiscall ImageRefractClass::ImageRefractClass(ImageRefractClass *this)

{
  SpecialItemClass::SpecialItemClass((SpecialItemClass *)this);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 0x49524546;
  *(char **)&this->field_0x10 = "imagerefract";
  return this;
}
