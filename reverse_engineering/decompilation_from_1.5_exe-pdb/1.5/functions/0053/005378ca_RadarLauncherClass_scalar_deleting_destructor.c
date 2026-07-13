/*
 * Entry: 005378ca
 * Name: RadarLauncherClass::`scalar_deleting_destructor'
 * Namespace: RadarLauncherClass
 * Signature: void * `scalar_deleting_destructor'(RadarLauncherClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
RadarLauncherClass::_scalar_deleting_destructor_(RadarLauncherClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  LauncherClass::~LauncherClass((LauncherClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
