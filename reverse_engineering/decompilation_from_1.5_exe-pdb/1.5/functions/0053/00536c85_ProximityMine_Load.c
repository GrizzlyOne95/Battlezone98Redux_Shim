/*
 * Entry: 00536c85
 * Name: ProximityMine::Load
 * Namespace: ProximityMine
 * Signature: bool Load(ProximityMine * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Removing unreachable block (ram,0x00536cde) */

bool __thiscall ProximityMine::Load(ProximityMine *this,_iobuf *param_1)

{
  float fVar1;
  bool bVar2;
  int iVar3;
  ulong uVar4;
  
  if ((version < 0x40e) || (missionSave)) {
    iVar3 = Net_IsNetGame();
    if (iVar3 == 0) {
      iVar3 = rand();
      fVar1 = (float)iVar3 * *(float *)(this->_padding_ + 0x16c) * 3.051851e-05;
    }
    else {
      uVar4 = DistributedObject::GetID((DistributedObject *)&this->_padding_);
      fVar1 = (float)(uVar4 & 0xf) * *(float *)(this->_padding_ + 0x16c) * 0.06666667;
    }
    this->searchTimer = fVar1;
  }
  else {
    bVar2 = ::in(param_1,&this->searchTimer,4);
    if (!bVar2) {
      return false;
    }
  }
  bVar2 = Mine::Load((Mine *)this,param_1);
  if (!bVar2) {
    return false;
  }
  return true;
}
