/*
 * Entry: 0046fad6
 * Name: UserProcess::Execute
 * Namespace: UserProcess
 * Signature: void Execute(UserProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UserProcess::Execute(UserProcess *this)

{
  uint *puVar1;
  float fVar2;
  short sVar3;
  Carrier *this_00;
  bool bVar4;
  int iVar5;
  SPHERE *pSVar6;
  GameObject *pGVar7;
  _OBJ76 *p_Var8;
  uint uVar9;
  uint uVar10;
  float *pfVar11;
  MAT_3D *pMVar12;
  Carrier *pCVar13;
  undefined4 *puVar14;
  MAT_3D *pMVar15;
  ulong uVar16;
  float fVar17;
  int iVar18;
  int iVar19;
  char *pcVar20;
  GAS_CTRL *pGVar21;
  MAT_3D local_48;
  Carrier *local_8;
  
  pCVar13 = *(Carrier **)(this->_padding_ + 0x198);
  local_8 = pCVar13;
  iVar5 = InputsEnabled();
  sVar3 = user_controls.key;
  if (iVar5 == 0) {
    memset(&user_controls,0,0x34);
    puVar14 = (undefined4 *)(*(int *)(this->_padding_ + 0x228) + 0xc4);
    user_controls.key = sVar3;
    for (iVar5 = 9; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar14 = 0;
      puVar14 = puVar14 + 1;
    }
  }
  if (((user_controls.drop_beacon != '\0') && (this->nav != (GameObjectClass *)0x0)) &&
     ((iVar5 = (*(code *)**(undefined4 **)(this->_padding_ + 0x20))(), *(int *)(iVar5 + 0x28) == 6
      || (iVar5 = (*(code *)**(undefined4 **)(this->_padding_ + 0x20))(),
         *(int *)(iVar5 + 0x28) == 1)))) {
    iVar5 = this->nav->categoryMin;
    if (((iVar5 == -1) || (iVar18 = this->nav->categoryMax, iVar18 == -1)) ||
       (iVar5 = Team::FirstEmptySlot(*(Team **)(this->_padding_ + 0x170),iVar5,iVar18), iVar5 != -1)
       ) {
      pGVar7 = (GameObject *)this->_padding_;
      pMVar12 = &pGVar7->obj->transform;
      pMVar15 = &local_48;
      for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
        pMVar15->right_x = pMVar12->right_x;
        pMVar12 = (MAT_3D *)&pMVar12->right_y;
        pMVar15 = (MAT_3D *)&pMVar15->right_y;
      }
      pSVar6 = GameObject::GetSphere(pGVar7);
      fVar17 = pSVar6->radius;
      pcVar20 = (char *)0x0;
      iVar19 = -1;
      iVar18 = 0;
      local_48.posit_x = (double)((float)local_48.posit_x - local_48.front_x * fVar17);
      local_48.posit_y = (double)((float)local_48.posit_y - local_48.front_y * fVar17);
      local_48.posit_z = (double)((float)local_48.posit_z - fVar17 * local_48.front_z);
      iVar5 = (**(code **)(*(int *)(this->_padding_ + 0x20) + 4))();
      pGVar7 = GameObjectClass::Build(this->nav,&local_48,iVar5,iVar18,iVar19,pcVar20);
      bVar4 = Net::IsNetGame();
      if (bVar4) {
        DistributedObject::SetLocal((DistributedObject *)&pGVar7->_padding_);
      }
      puVar1 = (uint *)(pGVar7[1]._padding_ + 0x10c);
      *puVar1 = *puVar1 | 4;
      pGVar21 = (GAS_CTRL *)0x0;
      p_Var8 = (_OBJ76 *)(**(code **)(pGVar7->_padding_ + 0x30))();
      DoAudioNew("gprox00.wav",p_Var8,pGVar21);
      pCVar13 = local_8;
    }
  }
  this_00 = local_8;
  if (pCVar13 != (Carrier *)0x0) {
    iVar5 = 0;
    uVar10 = pCVar13->selected;
    do {
      uVar9 = 1 << ((byte)iVar5 & 0x1f);
      uVar16 = uVar10;
      if ((((pCVar13->enabled & uVar9) != 0) && (user_controls.weapon_select[iVar5] != '\0')) &&
         (uVar16 = uVar9, command_controls.cmd_multi != '\0')) {
        uVar16 = uVar10 ^ uVar9;
      }
      iVar5 = iVar5 + 1;
      uVar10 = uVar16;
    } while (iVar5 < 5);
    if (user_controls.weapon_link != '\0') {
      uVar10 = (uint)(this->linked == 0);
      this->linked = uVar10;
      uVar16 = this->selectList[uVar10][this->cycle];
    }
    if (user_controls.weapon_cycle != '\0') {
      iVar5 = this->selectNext[this->linked][this->cycle];
      this->cycle = iVar5;
      uVar16 = this->selectList[this->linked][iVar5];
    }
    if (uVar16 != local_8->selected) {
      StartGASEvent("cammo.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0);
      Carrier::SetSelected(this_00,uVar16);
    }
    if (user_controls.weapon_fire != '\0') {
      Carrier::TriggerSelected(this_00);
    }
    if (user_controls.weapon_special != '\0') {
      Carrier::TriggerSpecial(this_00);
    }
  }
  fVar17 = TimeStepLocal();
  iVar5 = *(int *)(this->_padding_ + 0x228);
  pfVar11 = (float *)(iVar5 + 0xc4);
  if ((user_controls.steer_right == '\0') && (user_controls.steer_left == '\0')) {
    fVar2 = ((float)user_controls.steer * 1.5258789e-05 - *pfVar11) * fVar17 * 5.0;
  }
  else {
    fVar2 = ((float)((int)user_controls.steer_left - (int)user_controls.steer_right) - *pfVar11) *
            fVar17;
  }
  *pfVar11 = fVar2 + *pfVar11;
  if ((user_controls.pitch_up == '\0') && (user_controls.pitch_down == '\0')) {
    fVar2 = (float)user_controls.pitch * 1.5258789e-05;
    if ((UserProfilePtr->playOption & 0x40) != 0) {
      fVar2 = -fVar2;
    }
    fVar2 = (fVar2 - *(float *)(iVar5 + 200)) * fVar17 * 5.0;
  }
  else {
    fVar2 = ((float)((int)user_controls.pitch_down - (int)user_controls.pitch_up) -
            *(float *)(iVar5 + 200)) * fVar17;
  }
  *(float *)(iVar5 + 200) = fVar2 + *(float *)(iVar5 + 200);
  if ((user_controls.throttle_up == '\0') && (user_controls.throttle_down == '\0')) {
    fVar2 = (float)user_controls.throttle * 1.5258789e-05;
  }
  else {
    fVar2 = (float)((int)user_controls.throttle_up - (int)user_controls.throttle_down);
  }
  *(float *)(iVar5 + 0xd0) =
       (fVar2 - *(float *)(iVar5 + 0xd0)) * fVar17 * 3.0 + *(float *)(iVar5 + 0xd0);
  if ((user_controls.strafe_right == '\0') && (user_controls.strafe_left == '\0')) {
    fVar2 = (float)user_controls.strafe * 1.5258789e-05;
  }
  else {
    fVar2 = (float)((int)user_controls.strafe_right - (int)user_controls.strafe_left);
  }
  *(float *)(iVar5 + 0xcc) =
       (fVar2 - *(float *)(iVar5 + 0xcc)) * fVar17 * 3.0 + *(float *)(iVar5 + 0xcc);
  *(uint *)(iVar5 + 0xd4) = (uint)(user_controls.throttle == 0x10000) | (int)user_controls.turbo;
  *(int *)(iVar5 + 0xd8) = (int)user_controls.jump;
  *(int *)(iVar5 + 0xdc) = (int)user_controls.eject;
  *(int *)(iVar5 + 0xe0) = (int)user_controls.deploy;
  *(int *)(iVar5 + 0xe4) = (int)user_controls.abandon;
  return;
}
