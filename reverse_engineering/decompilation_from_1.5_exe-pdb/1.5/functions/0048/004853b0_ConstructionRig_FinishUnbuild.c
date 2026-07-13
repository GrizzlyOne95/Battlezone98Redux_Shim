/*
 * Entry: 004853b0
 * Name: ConstructionRig::FinishUnbuild
 * Namespace: ConstructionRig
 * Signature: void FinishUnbuild(ConstructionRig * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ConstructionRig::FinishUnbuild(ConstructionRig *this,GameObject *param_1)

{
  int *this_00;
  bool bVar1;
  int iVar2;
  
  Team::AddScrap((Team *)this->_padding_,this->dropClass->scrapValue);
  iVar2 = Net_IsNetGame();
  if (iVar2 != 0) {
    this_00 = &param_1->_padding_;
    bVar1 = DistributedObject::IsLocal((DistributedObject *)this_00);
    if (!bVar1) {
      iVar2 = Net_IsNetGame();
      if (iVar2 != 0) {
        bVar1 = DistributedObject::IsRemote((DistributedObject *)this_00);
        if (bVar1) {
          DistributedObject::RemoteDelete((DistributedObject *)this_00);
          DistributedObject::Destroy((DistributedObject *)this_00);
        }
      }
      goto LAB_00485410;
    }
  }
  (**(code **)(param_1->_padding_ + 0x10))();
LAB_00485410:
  this->unbuildHandle = 0;
  this->_padding_ = 0;
  return;
}
