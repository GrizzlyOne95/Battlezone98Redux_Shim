/*
 * Entry: 0053c276
 * Name: ThermalLauncherClass::`scalar_deleting_destructor'
 * Namespace: ThermalLauncherClass
 * Signature: void * `scalar_deleting_destructor'(ThermalLauncherClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
ThermalLauncherClass::_scalar_deleting_destructor_(ThermalLauncherClass *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  LauncherClass::~LauncherClass((LauncherClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
