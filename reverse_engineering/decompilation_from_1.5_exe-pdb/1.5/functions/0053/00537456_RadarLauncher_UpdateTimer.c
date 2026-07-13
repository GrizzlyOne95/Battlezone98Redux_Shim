/*
 * Entry: 00537456
 * Name: RadarLauncher::UpdateTimer
 * Namespace: RadarLauncher
 * Signature: void UpdateTimer(RadarLauncher * this, GameObject * param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RadarLauncher::UpdateTimer(RadarLauncher *this,GameObject *param_1,float param_2)

{
  int iVar1;
  
  iVar1 = (**(code **)param_1->_padding_)();
  *(float *)&this->field_0xac = *(float *)(iVar1 + 0xe4) * param_2 + *(float *)&this->field_0xac;
  return;
}
