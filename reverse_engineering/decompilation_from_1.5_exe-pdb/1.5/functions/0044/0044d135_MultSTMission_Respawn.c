/*
 * Entry: 0044d135
 * Name: MultSTMission::Respawn
 * Namespace: MultSTMission
 * Signature: void Respawn(MultSTMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MultSTMission::Respawn(MultSTMission *this)

{
  GameObjectClass *pGVar1;
  GameObject *pGVar2;
  tagENTITY *ptVar3;
  int iVar4;
  MAT_3D *pMVar5;
  int *this_00;
  MAT_3D *pMVar6;
  float fVar7;
  GKCommandKey GVar8;
  MAT_3D local_54;
  VECTOR_3D local_14;
  float local_8;
  
  if (Net::iLivesLeft < 1) {
    mission_stop = 1;
    if (NetEscapeUp == 0) {
      do_escape();
      return;
    }
  }
  else {
    pGVar1 = GameObjectClass::Find(CONCAT44(Net::odfName._4_4_,Net::odfName._0_4_));
    pGVar1 = pGVar1->userClass;
    Net::GetStartLocation(theNet,&local_14);
    pMVar5 = &Identity_Matrix;
    pMVar6 = &local_54;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      pMVar6->right_x = pMVar5->right_x;
      pMVar5 = (MAT_3D *)&pMVar5->right_y;
      pMVar6 = (MAT_3D *)&pMVar6->right_y;
    }
    local_8 = Random();
    fVar7 = Random();
    local_54.posit_x = (double)((local_8 - fVar7) * 20.0 + local_14.x);
    local_54.posit_y = (double)(local_14.y + 50.0);
    local_8 = Random();
    fVar7 = Random();
    local_54.posit_z = (double)((local_8 - fVar7) * 20.0 + local_14.z);
    pGVar2 = GameObjectClass::Build(pGVar1,&local_54,Net::Team,0,-1,(char *)0x0);
    (**(code **)(pGVar2->_padding_ + 0xc))();
    this_00 = &pGVar2->_padding_;
    (**(code **)(*this_00 + 8))(Net::Team);
    DistributedObject::SetLocal((DistributedObject *)this_00);
    do {
      iVar4 = Pop_Camera();
    } while (iVar4 != 0);
    EnableInputs();
    GVar8 = GK_COCKPIT_VIEW;
    ptVar3 = (tagENTITY *)(**(code **)(*this_00 + 0x2c))();
    Set_View(ptVar3,GVar8);
  }
  return;
}
