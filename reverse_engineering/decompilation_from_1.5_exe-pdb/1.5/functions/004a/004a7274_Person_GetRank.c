/*
 * Entry: 004a7274
 * Name: Person::GetRank
 * Namespace: Person
 * Signature: float GetRank(Person * this, float param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __thiscall Person::GetRank(Person *this,float param_1,float param_2)

{
  char cVar1;
  Weapon *pWVar2;
  int iVar3;
  float10 fVar4;
  
  if (param_1 < (float)this->_padding_) {
    this->_padding_ = (int)param_1;
  }
  param_1 = (param_1 - (float)this->_padding_) + (250.0 - param_2) * 0.004 * 5.0;
  fVar4 = (float10)(**(code **)(this->_padding_ + 0x1c))();
  if ((fVar4 != (float10)(float)this->_padding_) && (param_2 < 250.0)) {
    param_1 = param_1 + 1.0;
  }
  fVar4 = (float10)(**(code **)(this->_padding_ + 0x1c))();
  if ((fVar4 < (float10)0.0) || ((*(uint *)(this->_padding_ + 0x14) & 0x1000200) != 0)) {
    param_1 = param_1 + 10.0;
  }
  if (this->_padding_ != 0) {
    iVar3 = 0;
    do {
      pWVar2 = Carrier::GetWeapon((Carrier *)this->_padding_,iVar3);
      if (((pWVar2 != (Weapon *)0x0) && (pWVar2->weaponClass->sig == 0x534e4950)) &&
         (cVar1 = (**(code **)(pWVar2->_padding_ + 0x10))(), cVar1 != '\0')) {
        param_1 = param_1 + 2.0;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 5);
  }
  return param_1;
}
