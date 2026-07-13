/*
 * Entry: 00537564
 * Name: RadarLauncher::`scalar_deleting_destructor'
 * Namespace: RadarLauncher
 * Signature: void * `scalar_deleting_destructor'(RadarLauncher * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall RadarLauncher::_scalar_deleting_destructor_(RadarLauncher *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  Launcher::~Launcher((Launcher *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
