/*
 * Entry: 0053f80b
 * Name: WeaponMine::Cleanup
 * Namespace: WeaponMine
 * Signature: void Cleanup(WeaponMine * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall WeaponMine::Cleanup(WeaponMine *this)

{
  int iVar1;
  bool bVar2;
  
  bVar2 = false;
  iVar1 = (**(code **)(this->_padding_ + 4))();
  HazardCells((float)this->_padding_,(float)this->_padding_,*(float *)(this->_padding_ + 0x168),
              iVar1,bVar2);
  Building::Cleanup((Building *)this);
  return;
}
