/*
 * Entry: 004ae7c8
 * Name: Scavenger::Explode
 * Namespace: Scavenger
 * Signature: void Explode(Scavenger * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Scavenger::Explode(Scavenger *this)

{
  bool bVar1;
  int iVar2;
  VECTOR_3D *pVVar3;
  
  if ((this->_padding_ < 1) || ((*(byte *)(this->_padding_ + 0x14) & 0x80) != 0)) goto LAB_004ae820;
  iVar2 = Net_IsNetGame();
  if (iVar2 == 0) {
    iVar2 = this->_padding_;
  }
  else {
    bVar1 = Net::IsDeathMatch();
    if (bVar1) goto LAB_004ae820;
    bVar1 = DistributedObject::IsLocal((DistributedObject *)this);
    if (!bVar1) goto LAB_004ae820;
    iVar2 = this->_padding_ / 2;
  }
  pVVar3 = (VECTOR_3D *)(**(code **)(this->_padding_ + 0xc))();
  MakeScrapField(pVVar3,iVar2);
LAB_004ae820:
  Craft::Explode((Craft *)this);
  return;
}
