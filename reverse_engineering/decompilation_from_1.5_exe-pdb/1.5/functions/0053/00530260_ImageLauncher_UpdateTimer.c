/*
 * Entry: 00530260
 * Name: ImageLauncher::UpdateTimer
 * Namespace: ImageLauncher
 * Signature: void UpdateTimer(ImageLauncher * this, GameObject * param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ImageLauncher::UpdateTimer(ImageLauncher *this,GameObject *param_1,float param_2)

{
  int iVar1;
  
  iVar1 = (**(code **)param_1->_padding_)();
  *(float *)&this->field_0xac = *(float *)(iVar1 + 0xe0) * param_2 + *(float *)&this->field_0xac;
  return;
}
