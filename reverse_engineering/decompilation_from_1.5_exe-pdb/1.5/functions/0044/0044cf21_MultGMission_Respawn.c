/*
 * Entry: 0044cf21
 * Name: MultGMission::Respawn
 * Namespace: MultGMission
 * Signature: void Respawn(MultGMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall MultGMission::Respawn(MultGMission *this)

{
  int *this_00;
  float fVar1;
  float fVar2;
  char *pcVar3;
  char *pcVar4;
  AiPath *pAVar5;
  GameObject *pGVar6;
  GameObjectClass *pGVar7;
  tagENTITY *ptVar8;
  int iVar9;
  MAT_3D *pMVar10;
  MAT_3D *pMVar11;
  GKCommandKey GVar12;
  MAT_3D local_64;
  undefined4 local_24;
  GameObjectClass *local_20;
  char local_1c [20];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_24 = 0;
  local_20 = (GameObjectClass *)0x0;
  pcVar3 = Net::odfName;
  do {
    pcVar4 = pcVar3;
    pcVar3 = pcVar4 + 1;
  } while (*pcVar4 != '\0');
  memcpy(&local_24,Net::odfName,pcVar4 + -0x62a994);
  local_20 = GameObjectClass::Find(CONCAT44(local_20,local_24));
  sprintf(local_1c,"team%da",Net::Team);
  pAVar5 = AiPath::Find(local_1c);
  fVar1 = pAVar5->points->x;
  fVar2 = pAVar5->points->z;
  pMVar10 = &Identity_Matrix;
  pMVar11 = &local_64;
  for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
    pMVar11->right_x = pMVar10->right_x;
    pMVar10 = (MAT_3D *)&pMVar10->right_y;
    pMVar11 = (MAT_3D *)&pMVar11->right_y;
  }
  local_64.posit_x = (double)fVar1;
  local_64.posit_y = 0.0;
  local_64.posit_z = (double)fVar2;
  pGVar6 = GameObjectClass::Build(local_20,&local_64,Net::Team,1,-1,(char *)0x0);
  (**(code **)(pGVar6->_padding_ + 0xc))();
  this_00 = &pGVar6->_padding_;
  (**(code **)(*this_00 + 8))(Net::Team);
  DistributedObject::SetLocal((DistributedObject *)this_00);
  if (pGVar6->curPilot == (GameObjectClass *)0x0) {
    iVar9 = (**(code **)*this_00)();
    if (pGVar6 == GameObject::userObject) {
      pGVar7 = *(GameObjectClass **)(iVar9 + 0xdc);
    }
    else {
      pGVar7 = *(GameObjectClass **)(iVar9 + 0xd8);
    }
    pGVar6->curPilot = pGVar7;
  }
  do {
    iVar9 = Pop_Camera();
  } while (iVar9 != 0);
  EnableInputs();
  GVar12 = GK_COCKPIT_VIEW;
  ptVar8 = (tagENTITY *)(**(code **)(*this_00 + 0x2c))();
  Set_View(ptVar8,GVar12);
  return;
}
