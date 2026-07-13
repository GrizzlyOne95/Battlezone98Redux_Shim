/*
 * Entry: 004abad7
 * Name: Producer::Explode
 * Namespace: Producer
 * Signature: void Explode(Producer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Producer::Explode(Producer *this)

{
  bool bVar1;
  long lVar2;
  long lVar3;
  int iVar4;
  VECTOR_3D *pVVar5;
  int iVar6;
  
  HasPower((Producer *)(this[-1].smokeList + 5));
  if (this->_padding_ != 0) {
    Geizer::StartSteam((Geizer *)this->_padding_);
    BlockCells((GameObject *)(this[-1].smokeList + 5),false);
  }
  lVar2 = Team::GetMaxScrap((Team *)this->_padding_);
  iVar6 = *(int *)(this->_padding_ + 0x3d0);
  lVar3 = Team::GetScrap((Team *)this->_padding_);
  iVar6 = lVar3 + (iVar6 - lVar2);
  if ((0 < iVar6) && ((*(byte *)(this->_padding_ + 0x14) & 0x80) == 0)) {
    iVar4 = Net_IsNetGame();
    if (iVar4 != 0) {
      bVar1 = Net::IsDeathMatch();
      if ((bVar1) || (bVar1 = DistributedObject::IsLocal((DistributedObject *)this), !bVar1))
      goto LAB_004abb72;
      iVar6 = iVar6 / 2;
    }
    pVVar5 = (VECTOR_3D *)(**(code **)(this->_padding_ + 0xc))();
    MakeScrapField(pVVar5,iVar6);
  }
LAB_004abb72:
  Craft::Explode((Craft *)this);
  return;
}
