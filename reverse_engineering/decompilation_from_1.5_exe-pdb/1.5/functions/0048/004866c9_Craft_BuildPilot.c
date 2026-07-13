/*
 * Entry: 004866c9
 * Name: Craft::BuildPilot
 * Namespace: Craft
 * Signature: Craft * BuildPilot(Craft * this, GameObjectClass * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Craft * __thiscall Craft::BuildPilot(Craft *this,GameObjectClass *param_1)

{
  ulong *puVar1;
  MAT_3D *pMVar2;
  Craft *pCVar3;
  int iVar4;
  AiMission *pAVar5;
  int iVar6;
  MAT_3D *pMVar7;
  Craft *pCVar8;
  MAT_3D local_84;
  MAT_3D local_44;
  
  pMVar2 = obj_rel_parent_matrix(&local_84,this->vhcl->eyepoint,(_OBJ76 *)0x0);
  iVar4 = this->_padding_;
  pMVar7 = &local_44;
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    pMVar7->right_x = pMVar2->right_x;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
    pMVar7 = (MAT_3D *)&pMVar7->right_y;
  }
  local_44.posit_x = (double)(*(float *)(iVar4 + 0x14) * local_44.up_x + (float)local_44.posit_x);
  local_44.posit_y = (double)(*(float *)(iVar4 + 0x14) * local_44.up_y + (float)local_44.posit_y);
  local_44.posit_z = (double)(*(float *)(iVar4 + 0x14) * local_44.up_z + (float)local_44.posit_z);
  pCVar3 = (Craft *)GameObjectClass::Build(param_1,&local_44,this->_padding_,0,-1,(char *)0x0);
  puVar1 = &pCVar3->vhcl->flags;
  *puVar1 = *puVar1 | 8;
  iVar4 = Net_IsNetGame();
  if (iVar4 != 0) {
    DistributedObject::SetLocal((DistributedObject *)&pCVar3->_padding_);
  }
  if ((*(byte *)(this->_padding_ + 0x14) & 0x10) == 0) {
    pCVar8 = pCVar3;
    pAVar5 = AiMission::GetCurrent();
    AiProcess::Attach(pAVar5,(GameObject *)pCVar8);
  }
  else {
    (**(code **)(pCVar3->_padding_ + 0xc))();
  }
  (**(code **)(this->_padding_ + 8))(this->_padding_);
  return pCVar3;
}
