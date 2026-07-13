/*
 * Entry: 004b1104
 * Name: SpawnBuoy::Init
 * Namespace: SpawnBuoy
 * Signature: void Init(SpawnBuoy * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SpawnBuoy::Init(SpawnBuoy *this,int param_1)

{
  VECTOR_3D VVar1;
  bool bVar2;
  VECTOR_3D *pVVar3;
  SpawnPoint *pSVar4;
  
  Building::Init((Building *)this,param_1);
  bVar2 = Net::IsNetGame();
  if (bVar2) {
    pVVar3 = (VECTOR_3D *)(**(code **)(this->_padding_ + 0xc))();
    VVar1 = *pVVar3;
    pSVar4 = operator_new(0x14);
    if (pSVar4 == (SpawnPoint *)0x0) {
      pSVar4 = (SpawnPoint *)0x0;
    }
    else {
      pSVar4 = SpawnPoint::SpawnPoint(pSVar4,VVar1,param_1);
    }
    this->spawnPoint = pSVar4;
  }
  return;
}
