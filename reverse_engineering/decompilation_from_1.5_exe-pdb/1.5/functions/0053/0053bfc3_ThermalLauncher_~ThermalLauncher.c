/*
 * Entry: 0053bfc3
 * Name: ThermalLauncher::~ThermalLauncher
 * Namespace: ThermalLauncher
 * Signature: void ~ThermalLauncher(ThermalLauncher * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ThermalLauncher::~ThermalLauncher(ThermalLauncher *this)

{
  *(undefined ***)this = &_vftable_;
  Launcher::~Launcher((Launcher *)this);
  return;
}
