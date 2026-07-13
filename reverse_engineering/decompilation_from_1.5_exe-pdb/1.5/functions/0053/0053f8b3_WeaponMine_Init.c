/*
 * Entry: 0053f8b3
 * Name: WeaponMine::Init
 * Namespace: WeaponMine
 * Signature: void Init(WeaponMine * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall WeaponMine::Init(WeaponMine *this,int param_1)

{
  int iVar1;
  Weapon *pWVar2;
  Carrier *pCVar3;
  bool bVar4;
  
  Building::Init((Building *)this,param_1);
  bVar4 = true;
  iVar1 = (**(code **)(this->_padding_ + 4))();
  HazardCells((float)this->_padding_,(float)this->_padding_,*(float *)(this->_padding_ + 0x168),
              iVar1,bVar4);
  pWVar2 = WeaponClass::Build(*(WeaponClass **)(this->_padding_ + 0x170),(_OBJ76 *)this->_padding_,
                              (_OBJ76 *)this->_padding_);
  this->weapon = pWVar2;
  if (this->_padding_ == 0) {
    pCVar3 = operator_new(0x40);
    if (pCVar3 == (Carrier *)0x0) {
      pCVar3 = (Carrier *)0x0;
    }
    else {
      pCVar3 = Carrier::Carrier(pCVar3,(GameObject *)this);
    }
    this->_padding_ = (int)pCVar3;
  }
  Carrier::SetWeapon((Carrier *)this->_padding_,0,this->weapon);
  Carrier::SetHardpoint((Carrier *)this->_padding_,0,(_OBJ76 *)this->_padding_);
  *(uint *)(this->_padding_ + 0x34) = *(uint *)(this->_padding_ + 0x2c) & 1;
  Carrier::SetSelected((Carrier *)this->_padding_,1);
  (**(code **)(this->weapon->_padding_ + 0x14))(0x38d1b717);
  return;
}
