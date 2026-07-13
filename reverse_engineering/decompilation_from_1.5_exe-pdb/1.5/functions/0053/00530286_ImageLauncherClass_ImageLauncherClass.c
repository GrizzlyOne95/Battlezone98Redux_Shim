/*
 * Entry: 00530286
 * Name: ImageLauncherClass::ImageLauncherClass
 * Namespace: ImageLauncherClass
 * Signature: ImageLauncherClass * ImageLauncherClass(ImageLauncherClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ImageLauncherClass * __thiscall ImageLauncherClass::ImageLauncherClass(ImageLauncherClass *this)

{
  LauncherClass::LauncherClass((LauncherClass *)this);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 0x494d474c;
  *(char **)&this->field_0x10 = "imagelauncher";
  return this;
}
