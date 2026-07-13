/*
 * Entry: 004825a4
 * Name: Barracks::BuildPilot
 * Namespace: Barracks
 * Signature: Craft * BuildPilot(Barracks * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Craft * __thiscall Barracks::BuildPilot(Barracks *this)

{
  ulong *puVar1;
  GameObjectClass *this_00;
  Craft *pCVar2;
  int iVar3;
  AiMission *pAVar4;
  VECTOR_3D *pVVar5;
  int iVar6;
  float *pfVar7;
  MAT_3D *pMVar8;
  MAT_3D local_60;
  VECTOR_3D local_20;
  VECTOR_3D local_14;
  Craft *local_8;
  
  this_00 = *(GameObjectClass **)(this->_padding_ + 0x164);
  local_8 = (Craft *)0x0;
  if (this_00 != (GameObjectClass *)0x0) {
    iVar3 = this->_padding_;
    pfVar7 = (float *)(this->_padding_ + 0x20);
    pMVar8 = &local_60;
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      pMVar8->right_x = *pfVar7;
      pfVar7 = pfVar7 + 1;
      pMVar8 = (MAT_3D *)&pMVar8->right_y;
    }
    pCVar2 = (Craft *)GameObjectClass::Build(this_00,&local_60,iVar3,0,-1,(char *)0x0);
    puVar1 = &pCVar2->vhcl->flags;
    *puVar1 = *puVar1 | 0xc;
    local_8 = pCVar2;
    iVar3 = Net_IsNetGame();
    if (iVar3 != 0) {
      DistributedObject::SetLocal((DistributedObject *)&pCVar2->_padding_);
    }
    pAVar4 = AiMission::GetCurrent();
    AiProcess::Attach(pAVar4,(GameObject *)pCVar2);
    iVar3 = this->_padding_;
    local_14.x = ((VECTOR_3D *)(iVar3 + 0x2c))->x;
    local_14.y = *(float *)(iVar3 + 0x30);
    local_14.z = *(float *)(iVar3 + 0x34);
    pVVar5 = ScaleVector(&local_20,20.0,*(VECTOR_3D *)(iVar3 + 0x2c));
    local_14.x = pVVar5->x;
    local_14.y = pVVar5->y;
    local_14.z = pVVar5->z;
    GameObject::SetVelocity((GameObject *)local_8,&local_14);
  }
  return local_8;
}
