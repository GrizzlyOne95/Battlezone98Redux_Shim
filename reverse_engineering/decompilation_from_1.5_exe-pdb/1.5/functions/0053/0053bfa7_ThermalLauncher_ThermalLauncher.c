/*
 * Entry: 0053bfa7
 * Name: ThermalLauncher::ThermalLauncher
 * Namespace: ThermalLauncher
 * Signature: ThermalLauncher * ThermalLauncher(ThermalLauncher * this, _OBJ76 * param_1, ThermalLauncherClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ThermalLauncher * __thiscall
ThermalLauncher::ThermalLauncher
          (ThermalLauncher *this,_OBJ76 *param_1,ThermalLauncherClass *param_2)

{
  Launcher::Launcher((Launcher *)this,param_1,(LauncherClass *)param_2);
  *(undefined ***)this = &_vftable_;
  return this;
}
