/*
 * Entry: 005304da
 * Name: ImageLauncherClass::`scalar_deleting_destructor'
 * Namespace: ImageLauncherClass
 * Signature: void * `scalar_deleting_destructor'(ImageLauncherClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
ImageLauncherClass::_scalar_deleting_destructor_(ImageLauncherClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  LauncherClass::~LauncherClass((LauncherClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
