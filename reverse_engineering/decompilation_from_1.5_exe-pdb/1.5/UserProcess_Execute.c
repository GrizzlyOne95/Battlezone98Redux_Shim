
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall UserProcess::Execute(UserProcess *this)

{
  uint *puVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  short sVar5;
  Carrier *this_00;
  bool bVar6;
  int iVar7;
  SPHERE *pSVar8;
  GameObject *pGVar9;
  _OBJ76 *p_Var10;
  uint uVar11;
  uint uVar12;
  float *pfVar13;
  MAT_3D *pMVar14;
  Carrier *pCVar15;
  undefined4 *puVar16;
  MAT_3D *pMVar17;
  ulong uVar18;
  float fVar19;
  int iVar20;
  int iVar21;
  char *pcVar22;
  GAS_CTRL *pGVar23;
  MAT_3D local_48;
  Carrier *local_8;
  
  pCVar15 = *(Carrier **)(this->_padding_ + 0x198);
  local_8 = pCVar15;
  iVar7 = InputsEnabled();
  sVar5 = user_controls.key;
  if (iVar7 == 0) {
    memset(&user_controls,0,0x34);
    puVar16 = (undefined4 *)(*(int *)(this->_padding_ + 0x228) + 0xc4);
    user_controls.key = sVar5;
    for (iVar7 = 9; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar16 = 0;
      puVar16 = puVar16 + 1;
    }
  }
  if (((user_controls.drop_beacon != '\0') && (this->nav != (GameObjectClass *)0x0)) &&
     ((iVar7 = (*(code *)**(undefined4 **)(this->_padding_ + 0x20))(), *(int *)(iVar7 + 0x28) == 6
      || (iVar7 = (*(code *)**(undefined4 **)(this->_padding_ + 0x20))(),
         *(int *)(iVar7 + 0x28) == 1)))) {
    iVar7 = this->nav->categoryMin;
    if (((iVar7 == -1) || (iVar20 = this->nav->categoryMax, iVar20 == -1)) ||
       (iVar7 = Team::FirstEmptySlot(*(Team **)(this->_padding_ + 0x170),iVar7,iVar20), iVar7 != -1)
       ) {
      pGVar9 = (GameObject *)this->_padding_;
      pMVar14 = &pGVar9->obj->transform;
      pMVar17 = &local_48;
      for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
        pMVar17->right_x = pMVar14->right_x;
        pMVar14 = (MAT_3D *)&pMVar14->right_y;
        pMVar17 = (MAT_3D *)&pMVar17->right_y;
      }
      pSVar8 = GameObject::GetSphere(pGVar9);
      fVar2 = pSVar8->radius;
      pcVar22 = (char *)0x0;
      iVar21 = -1;
      iVar20 = 0;
      local_48.posit_x = (double)((float)local_48.posit_x - local_48.front_x * fVar2);
      local_48.posit_y = (double)((float)local_48.posit_y - local_48.front_y * fVar2);
      local_48.posit_z = (double)((float)local_48.posit_z - fVar2 * local_48.front_z);
      iVar7 = (**(code **)(*(int *)(this->_padding_ + 0x20) + 4))();
      pGVar9 = GameObjectClass::Build(this->nav,&local_48,iVar7,iVar20,iVar21,pcVar22);
      bVar6 = Net::IsNetGame();
      if (bVar6) {
        DistributedObject::SetLocal((DistributedObject *)&pGVar9->_padding_);
      }
      puVar1 = (uint *)(pGVar9[1]._padding_ + 0x10c);
      *puVar1 = *puVar1 | 4;
      pGVar23 = (GAS_CTRL *)0x0;
      p_Var10 = (_OBJ76 *)(**(code **)(pGVar9->_padding_ + 0x30))();
      DoAudioNew("gprox00.wav",p_Var10,pGVar23);
      pCVar15 = local_8;
    }
  }
  this_00 = local_8;
  if (pCVar15 != (Carrier *)0x0) {
    iVar7 = 0;
    uVar12 = pCVar15->selected;
    do {
      uVar11 = 1 << ((byte)iVar7 & 0x1f);
      uVar18 = uVar12;
      if ((((pCVar15->enabled & uVar11) != 0) && (user_controls.weapon_select[iVar7] != '\0')) &&
         (uVar18 = uVar11, command_controls.cmd_multi != '\0')) {
        uVar18 = uVar12 ^ uVar11;
      }
      iVar7 = iVar7 + 1;
      uVar12 = uVar18;
    } while (iVar7 < 5);
    if (user_controls.weapon_link != '\0') {
      uVar12 = (uint)(this->linked == 0);
      this->linked = uVar12;
      uVar18 = this->selectList[uVar12][this->cycle];
    }
    if (user_controls.weapon_cycle != '\0') {
      iVar7 = this->selectNext[this->linked][this->cycle];
      this->cycle = iVar7;
      uVar18 = this->selectList[this->linked][iVar7];
    }
    if (uVar18 != local_8->selected) {
      StartGASEvent("cammo.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0);
      Carrier::SetSelected(this_00,uVar18);
    }
    if (user_controls.weapon_fire != '\0') {
      Carrier::TriggerSelected(this_00);
    }
    if (user_controls.weapon_special != '\0') {
      Carrier::TriggerSpecial(this_00);
    }
  }
  fVar19 = TimeStepLocal();
  fVar4 = ___real_37800000;
  fVar2 = ___real_40a00000;
  iVar7 = *(int *)(this->_padding_ + 0x228);
  pfVar13 = (float *)(iVar7 + 0xc4);
  if ((user_controls.steer_right == '\0') && (user_controls.steer_left == '\0')) {
    fVar3 = ((float)user_controls.steer * ___real_37800000 - *pfVar13) * fVar19 * ___real_40a00000;
  }
  else {
    fVar3 = ((float)((int)user_controls.steer_left - (int)user_controls.steer_right) - *pfVar13) *
            fVar19;
  }
  *pfVar13 = fVar3 + *pfVar13;
  if ((user_controls.pitch_up == '\0') && (user_controls.pitch_down == '\0')) {
    fVar3 = (float)user_controls.pitch * fVar4;
    if ((UserProfilePtr->playOption & 0x40) != 0) {
      fVar3 = -fVar3;
    }
    fVar2 = (fVar3 - *(float *)(iVar7 + 200)) * fVar19 * fVar2;
  }
  else {
    fVar2 = ((float)((int)user_controls.pitch_down - (int)user_controls.pitch_up) -
            *(float *)(iVar7 + 200)) * fVar19;
  }
  *(float *)(iVar7 + 200) = fVar2 + *(float *)(iVar7 + 200);
  fVar2 = ___real_40400000;
  if ((user_controls.throttle_up == '\0') && (user_controls.throttle_down == '\0')) {
    fVar3 = (float)user_controls.throttle * fVar4;
  }
  else {
    fVar3 = (float)((int)user_controls.throttle_up - (int)user_controls.throttle_down);
  }
  *(float *)(iVar7 + 0xd0) =
       (fVar3 - *(float *)(iVar7 + 0xd0)) * fVar19 * ___real_40400000 + *(float *)(iVar7 + 0xd0);
  if ((user_controls.strafe_right == '\0') && (user_controls.strafe_left == '\0')) {
    fVar4 = (float)user_controls.strafe * fVar4;
  }
  else {
    fVar4 = (float)((int)user_controls.strafe_right - (int)user_controls.strafe_left);
  }
  *(float *)(iVar7 + 0xcc) =
       fVar2 * (fVar4 - *(float *)(iVar7 + 0xcc)) * fVar19 + *(float *)(iVar7 + 0xcc);
  *(uint *)(iVar7 + 0xd4) = (uint)(user_controls.throttle == 0x10000) | (int)user_controls.turbo;
  *(int *)(iVar7 + 0xd8) = (int)user_controls.jump;
  *(int *)(iVar7 + 0xdc) = (int)user_controls.eject;
  *(int *)(iVar7 + 0xe0) = (int)user_controls.deploy;
  *(int *)(iVar7 + 0xe4) = (int)user_controls.abandon;
  return;
}


