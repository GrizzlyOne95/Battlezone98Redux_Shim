/*
 * Entry: 0053c08f
 * Name: ThermalLauncher::`scalar_deleting_destructor'
 * Namespace: ThermalLauncher
 * Signature: void * `scalar_deleting_destructor'(ThermalLauncher * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ThermalLauncher::_scalar_deleting_destructor_(ThermalLauncher *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  Launcher::~Launcher((Launcher *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
