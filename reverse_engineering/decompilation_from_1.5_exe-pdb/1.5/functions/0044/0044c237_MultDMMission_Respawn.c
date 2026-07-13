/*
 * Entry: 0044c237
 * Name: MultDMMission::Respawn
 * Namespace: MultDMMission
 * Signature: void Respawn(MultDMMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MultDMMission::Respawn(MultDMMission *this)

{
  int *this_00;
  float fVar1;
  char *pcVar2;
  char *pcVar3;
  SpawnPoint *this_01;
  VECTOR_3D *pVVar4;
  GameObject *pGVar5;
  GameObjectClass *pGVar6;
  tagENTITY *ptVar7;
  int iVar8;
  MAT_3D *pMVar9;
  MAT_3D *pMVar10;
  GKCommandKey GVar11;
  MAT_3D local_58;
  VECTOR_3D local_18;
  undefined4 local_c;
  GameObjectClass *local_8;
  
  local_c = 0;
  local_8 = (GameObjectClass *)0x0;
  pcVar2 = Net::odfName;
  do {
    pcVar3 = pcVar2;
    pcVar2 = pcVar3 + 1;
  } while (*pcVar3 != '\0');
  memcpy(&local_c,Net::odfName,pcVar3 + -0x62a994);
  local_8 = GameObjectClass::Find(CONCAT44(local_8,local_c));
  Net::GetStartLocation(theNet,&local_18);
  this_01 = SpawnPoint::GetWeighted(Net::Team);
  if (this_01 != (SpawnPoint *)0x0) {
    pVVar4 = SpawnPoint::GetLocation(this_01);
    local_18.x = pVVar4->x;
    local_18.y = pVVar4->y;
    local_18.z = pVVar4->z;
  }
  fVar1 = local_18.x;
  pMVar9 = &Identity_Matrix;
  pMVar10 = &local_58;
  for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
    pMVar10->right_x = pMVar9->right_x;
    pMVar9 = (MAT_3D *)&pMVar9->right_y;
    pMVar10 = (MAT_3D *)&pMVar10->right_y;
  }
  local_58.posit_x = (double)fVar1;
  local_58.posit_y = (double)local_18.y;
  local_58.posit_z = (double)local_18.z;
  pGVar5 = GameObjectClass::Build(local_8,&local_58,Net::Team,0,-1,(char *)0x0);
  (**(code **)(pGVar5->_padding_ + 0xc))();
  this_00 = &pGVar5->_padding_;
  (**(code **)(*this_00 + 8))(Net::Team);
  DistributedObject::SetLocal((DistributedObject *)this_00);
  if (pGVar5->curPilot == (GameObjectClass *)0x0) {
    iVar8 = (**(code **)*this_00)();
    if (pGVar5 == GameObject::userObject) {
      pGVar6 = *(GameObjectClass **)(iVar8 + 0xdc);
    }
    else {
      pGVar6 = *(GameObjectClass **)(iVar8 + 0xd8);
    }
    pGVar5->curPilot = pGVar6;
  }
  do {
    iVar8 = Pop_Camera();
  } while (iVar8 != 0);
  EnableInputs();
  GVar11 = GK_COCKPIT_VIEW;
  ptVar7 = (tagENTITY *)(**(code **)(*this_00 + 0x2c))();
  Set_View(ptVar7,GVar11);
  return;
}
