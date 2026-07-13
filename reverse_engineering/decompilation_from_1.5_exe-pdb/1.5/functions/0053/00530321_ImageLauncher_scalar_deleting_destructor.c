/*
 * Entry: 00530321
 * Name: ImageLauncher::`scalar_deleting_destructor'
 * Namespace: ImageLauncher
 * Signature: void * `scalar_deleting_destructor'(ImageLauncher * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ImageLauncher::_scalar_deleting_destructor_(ImageLauncher *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  Launcher::~Launcher((Launcher *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
