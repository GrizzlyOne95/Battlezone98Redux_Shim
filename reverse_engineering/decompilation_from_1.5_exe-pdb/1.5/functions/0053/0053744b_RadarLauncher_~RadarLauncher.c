/*
 * Entry: 0053744b
 * Name: RadarLauncher::~RadarLauncher
 * Namespace: RadarLauncher
 * Signature: void ~RadarLauncher(RadarLauncher * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RadarLauncher::~RadarLauncher(RadarLauncher *this)

{
  *(undefined ***)this = &_vftable_;
  Launcher::~Launcher((Launcher *)this);
  return;
}
