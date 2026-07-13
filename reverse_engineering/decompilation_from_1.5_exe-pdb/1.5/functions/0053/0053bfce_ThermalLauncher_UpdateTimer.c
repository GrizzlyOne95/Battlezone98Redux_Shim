/*
 * Entry: 0053bfce
 * Name: ThermalLauncher::UpdateTimer
 * Namespace: ThermalLauncher
 * Signature: void UpdateTimer(ThermalLauncher * this, GameObject * param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
ThermalLauncher::UpdateTimer(ThermalLauncher *this,GameObject *param_1,float param_2)

{
  int iVar1;
  
  iVar1 = (**(code **)param_1->_padding_)();
  *(float *)&this->field_0xac = *(float *)(iVar1 + 0xe8) * param_2 + *(float *)&this->field_0xac;
  return;
}
