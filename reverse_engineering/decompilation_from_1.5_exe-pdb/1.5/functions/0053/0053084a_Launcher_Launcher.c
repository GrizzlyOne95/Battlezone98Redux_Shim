/*
 * Entry: 0053084a
 * Name: Launcher::Launcher
 * Namespace: Launcher
 * Signature: Launcher * Launcher(Launcher * this, _OBJ76 * param_1, LauncherClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Launcher * __thiscall Launcher::Launcher(Launcher *this,_OBJ76 *param_1,LauncherClass *param_2)

{
  int iVar1;
  float fVar2;
  GameObject *pGVar3;
  float10 fVar4;
  
  Weapon::Weapon((Weapon *)this,param_1,(WeaponClass *)param_2);
  this->shotTimer = 0.0;
  this->_padding_ = (int)&_vftable_;
  this->lockTimer = 0.0;
  iVar1 = param_2->targetCount;
  fVar2 = param_2->lockDelay;
  this->lockState = 0;
  this->lockDelay = fVar2 / (float)iVar1;
  fVar4 = (float10)fsin((float10)param_2->coneAngle);
  this->go = (_gas_object *)0x0;
  this->coneSinSq = (float)(fVar4 * fVar4);
  if (this->_padding_ == 0) {
    pGVar3 = (GameObject *)0x0;
  }
  else {
    pGVar3 = *(GameObject **)(this->_padding_ + 0xb4);
  }
  this->carrier = pGVar3;
  this->curTarget = 0;
  this->lockTarget = 0;
  this->triggered = false;
  this->selected = false;
  return this;
}
