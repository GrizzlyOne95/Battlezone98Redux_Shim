/*
 * Entry: 004d997d
 * Name: Reticle::Simulate
 * Namespace: Reticle
 * Signature: void Simulate(Reticle * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Reticle::Simulate(Reticle *this,float param_1)

{
  float fVar1;
  float fVar2;
  Carrier *this_00;
  uint uVar3;
  int iVar4;
  MAT_3D *pMVar5;
  GameObject *pGVar6;
  AiCommand AVar7;
  VECTOR_3D *pVVar8;
  Weapon *pWVar9;
  MAT_3D *pMVar10;
  double dVar11;
  MAT_3D local_88;
  MAT_3D local_48;
  GameObject *local_8;
  
  pGVar6 = GameObject::userObject;
  local_8 = GameObject::userObject;
  if (GameObject::userObject == (GameObject *)0x0) {
    return;
  }
  iVar4 = (**(code **)(GameObject::userObject->_padding_ + 0x30))();
  if ((*(uint *)(iVar4 + 0x14) & 0x200) != 0) {
    return;
  }
  pMVar5 = obj_rel_parent_matrix(&local_88,*(_OBJ76 **)(pGVar6[1]._padding_ + 0xf4),(_OBJ76 *)0x0);
  pGVar6 = local_8;
  pMVar10 = &local_48;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar10->right_x = pMVar5->right_x;
    pMVar5 = (MAT_3D *)&pMVar5->right_y;
    pMVar10 = (MAT_3D *)&pMVar10->right_y;
  }
  pMVar5 = &pGVar6->obj->transform;
  pMVar10 = &this->sightMat;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar10->right_x = pMVar5->right_x;
    pMVar5 = (MAT_3D *)&pMVar5->right_y;
    pMVar10 = (MAT_3D *)&pMVar10->right_y;
  }
  (this->sightMat).posit_x = local_48.posit_x;
  (this->sightMat).posit_y = local_48.posit_y;
  (this->sightMat).posit_z = local_48.posit_z;
  fVar1 = (this->sightMat).front_z;
  fVar2 = (this->sightMat).front_x;
  dVar11 = rsqrt((double)(fVar2 * fVar2 + fVar1 * fVar1));
  (this->horizMat).up_x = 0.0;
  (this->horizMat).up_y = 1.0;
  (this->horizMat).up_z = 0.0;
  fVar1 = (this->sightMat).front_x * (float)dVar11;
  (this->horizMat).front_x = fVar1;
  (this->horizMat).front_y = 0.0;
  fVar2 = (this->sightMat).front_z * (float)dVar11;
  (this->horizMat).front_z = fVar2;
  (this->horizMat).right_x = fVar2;
  (this->horizMat).right_y = 0.0;
  (this->horizMat).right_z = -fVar1;
  (this->horizMat).posit_x = (this->sightMat).posit_x;
  (this->horizMat).posit_y = (this->sightMat).posit_y;
  (this->horizMat).posit_z = (this->sightMat).posit_z;
  if ((((View_Record.Current_View != COCKPIT_VIEW) && (View_Record.Current_View != BINOCULAR_VIEW))
      && (View_Record.Current_View != FIX_EXTERN_VIEW)) && (View_Record.Current_View != CHASE_VIEW))
  {
    this->selectObj = (GameObject *)0x0;
    this->groundPos = (VECTOR_3D *)0x0;
    goto LAB_004d9b78;
  }
  pMVar5 = Build_Pitch_Matrix(&local_88,-(float)local_8[1]._padding_);
  pMVar10 = &local_48;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar10->right_x = pMVar5->right_x;
    pMVar5 = (MAT_3D *)&pMVar5->right_y;
    pMVar10 = (MAT_3D *)&pMVar10->right_y;
  }
  pMVar5 = Matrix_Multiply(&local_88,&local_48,&this->sightMat);
  pMVar10 = &this->sightMat;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar10->right_x = pMVar5->right_x;
    pMVar5 = (MAT_3D *)&pMVar5->right_y;
    pMVar10 = (MAT_3D *)&pMVar10->right_y;
  }
  this->startCommand = CMD_NONE;
  if ((controlPanel.selectNum == 0) || (command_controls.cmd_multi != '\0')) {
    pGVar6 = (GameObject *)0x0;
  }
  else {
    pGVar6 = GameObject::GetObj(controlPanel.selectList[0]);
  }
  pGVar6 = FindReticleObject(this,pGVar6);
  this->selectObj = pGVar6;
  if (pGVar6 == (GameObject *)0x0) {
    pVVar8 = FindGroundPos(this);
    this->groundPos = pVVar8;
    if (pVVar8 != (VECTOR_3D *)0x0) {
      AVar7 = ActionMode::GetCommand(&actionMode,pVVar8);
      goto LAB_004d9b44;
    }
  }
  else {
    this->groundPos = (VECTOR_3D *)0x0;
    AVar7 = ActionMode::GetCommand(&actionMode,pGVar6);
LAB_004d9b44:
    this->startCommand = AVar7;
  }
  if (this->selectObj == (GameObject *)0x0) {
    ControlPanel::SetCommand(&controlPanel,this->startCommand,this->groundPos);
  }
  else {
    ControlPanel::SetCommand(&controlPanel,this->startCommand,this->selectObj);
  }
LAB_004d9b78:
  this->ladderIndex = 0;
  this->reticleIndex = this->defaultIndex;
  this_00 = local_8->carrier;
  if (this_00 != (Carrier *)0x0) {
    uVar3 = this_00->selected;
    local_8 = (GameObject *)0x0;
    do {
      if (((uVar3 & 1 << ((byte)local_8 & 0x1f)) != 0) &&
         (pWVar9 = Carrier::GetWeapon(this_00,(int)local_8), pWVar9->wpnReticle != 0)) {
        this->reticleIndex = pWVar9->wpnReticle;
        this->ladderIndex = pWVar9->weaponClass->wpnLadder;
        return;
      }
      local_8 = (GameObject *)((int)local_8 + 1);
    } while ((int)local_8 < 5);
  }
  return;
}
