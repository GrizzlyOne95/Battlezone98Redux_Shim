/*
 * Entry: 00530672
 * Name: ImageRefractClass::ImageRefractClass
 * Namespace: ImageRefractClass
 * Signature: ImageRefractClass * ImageRefractClass(ImageRefractClass * this, ImageRefractClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ImageRefractClass * __thiscall
ImageRefractClass::ImageRefractClass
          (ImageRefractClass *this,ImageRefractClass *param_1,long64 param_2)

{
  undefined4 unaff_ESI;
  
  SpecialItemClass::SpecialItemClass
            ((SpecialItemClass *)this,(SpecialItemClass *)param_1,
             CONCAT44(unaff_ESI,(undefined4)param_2));
  *(undefined ***)this = &_vftable_;
  return this;
}
