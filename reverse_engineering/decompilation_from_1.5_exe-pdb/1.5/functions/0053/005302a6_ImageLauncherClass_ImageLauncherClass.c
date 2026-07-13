/*
 * Entry: 005302a6
 * Name: ImageLauncherClass::ImageLauncherClass
 * Namespace: ImageLauncherClass
 * Signature: ImageLauncherClass * ImageLauncherClass(ImageLauncherClass * this, ImageLauncherClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ImageLauncherClass * __thiscall
ImageLauncherClass::ImageLauncherClass
          (ImageLauncherClass *this,ImageLauncherClass *param_1,long64 param_2)

{
  undefined4 unaff_ESI;
  
  LauncherClass::LauncherClass
            ((LauncherClass *)this,(LauncherClass *)param_1,CONCAT44(unaff_ESI,(undefined4)param_2))
  ;
  *(undefined ***)this = &_vftable_;
  return this;
}
