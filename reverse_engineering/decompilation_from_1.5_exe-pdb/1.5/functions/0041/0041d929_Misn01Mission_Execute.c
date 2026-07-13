/*
 * Entry: 0041d929
 * Name: Misn01Mission::Execute
 * Namespace: Misn01Mission
 * Signature: void Execute(Misn01Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn01Mission::Execute(Misn01Mission *this)

{
  int *piVar1;
  VECTOR_2D *pVVar2;
  float fVar3;
  VECTOR_2D VVar4;
  VECTOR_2D VVar5;
  VECTOR_2D VVar6;
  VECTOR_2D VVar7;
  VECTOR_2D VVar8;
  VECTOR_2D VVar9;
  VECTOR_2D VVar10;
  VECTOR_2D VVar11;
  VECTOR_2D VVar12;
  VECTOR_2D VVar13;
  VECTOR_2D VVar14;
  VECTOR_2D VVar15;
  VECTOR_2D VVar16;
  VECTOR_2D VVar17;
  VECTOR_2D VVar18;
  VECTOR_2D VVar19;
  GameObject *pGVar20;
  bool bVar21;
  float *pfVar22;
  int iVar23;
  AiPath *pAVar24;
  GameObject *pGVar25;
  VECTOR_3D *pVVar26;
  VECTOR_3D *pVVar27;
  VECTOR_2D VVar28;
  VECTOR_2D VVar29;
  float fVar30;
  float fVar31;
  char *pcVar32;
  VECTOR_2D local_2c;
  float local_20;
  float local_1c;
  VECTOR_2D local_10;
  int local_8;
  
  pGVar20 = GameObject::userObject;
  local_8 = GetPlayerHandle();
  bVar21 = IsAlive(&local_8);
  if (bVar21) {
    pfVar22 = (float *)(**(code **)(pGVar20->_padding_ + 0xc))();
    local_20 = *pfVar22;
    local_1c = pfVar22[2];
    local_2c.z = local_1c;
    local_2c.x = local_20;
  }
  if ((this->field16_0x40)._s_0.start_done == false) {
    iVar23 = GetHandle("avfigh0_wingman");
    (this->field18_0x64)._s_0.get_in_me = iVar23;
    iVar23 = AudioMessage("misn0101.wav");
    (this->field20_0x88)._s_0.aud = iVar23;
    pAVar24 = AiPath::Find("path_1");
    (this->field19_0x74)._s_0.p1 = pAVar24;
    pAVar24 = AiPath::Find("path_2");
    (this->field19_0x74)._s_0.p2 = pAVar24;
    pAVar24 = AiPath::Find("path_3");
    (this->field19_0x74)._s_0.p3 = pAVar24;
    pAVar24 = AiPath::Find("path_5");
    (this->field19_0x74)._s_0.p4 = pAVar24;
    iVar23 = GetHandle("svturr0_turrettank");
    (this->field18_0x64)._s_0.target = iVar23;
    iVar23 = GetHandle("svturr1_turrettank");
    (this->field18_0x64)._s_0.target2 = iVar23;
    (this->field16_0x40)._s_0.start_done = true;
    fVar30 = Get_Time();
    (this->field17_0x54)._s_0.repeat_time = fVar30 + 30.0;
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"misn0101.otf",DisplayInterface::colorWhite,8.0);
    InfoDisplay::AddObjective(&infoDisplay,"misn0103.otf",DisplayInterface::colorWhite,8.0);
    (this->field20_0x88)._s_0.num_reps = 0;
  }
  pGVar25 = GameObjectHandle::GetObj((this->field18_0x64)._s_0.target);
  if ((this->field16_0x40)._s_0.start_path1 == false) {
    fVar30 = Get_Time();
    if ((this->field17_0x54)._s_0.repeat_time < fVar30) {
      fVar30 = Get_Time();
      (this->field17_0x54)._s_0.repeat_time = fVar30 + 20.0;
      InfoDisplay::ClearObjectives(&infoDisplay);
      InfoDisplay::AddObjective(&infoDisplay,"misn0101.otf",DisplayInterface::colorGreen,8.0);
      piVar1 = &(this->field20_0x88)._s_0.num_reps;
      *piVar1 = *piVar1 + 1;
    }
    if ((this->field16_0x40)._s_0.start_path1 != false) goto LAB_0041dba9;
    VVar28.z = local_1c;
    VVar28.x = local_20;
    VVar28 = Vec2D_Subtract(*((this->field19_0x74)._s_0.p1)->points,VVar28);
    local_10.z = VVar28.z;
    if (SQRT(local_10.z * local_10.z + local_10.x * local_10.x) <
        (this->field17_0x54)._s_0.forgiveness) {
      if ((local_8 == (this->field18_0x64)._s_0.get_in_me) ||
         ((this->field16_0x40)._s_0.hop_in != false)) {
        InfoDisplay::ClearObjectives(&infoDisplay);
        InfoDisplay::AddObjective(&infoDisplay,"misn0101.otf",DisplayInterface::colorGreen,8.0);
        InfoDisplay::AddObjective(&infoDisplay,"misn0103.otf",DisplayInterface::colorWhite,8.0);
      }
      else {
        iVar23 = (this->field20_0x88)._s_0.aud;
        (this->field16_0x40)._s_0.hop_in = true;
        StopAudioMessage(iVar23);
        AudioMessage("misn0122.wav");
      }
      StartCockpitTimerUp(0,300,0xf0);
      (this->field17_0x54)._s_0.repeat_time = 0.0;
      (this->field20_0x88)._s_0.num_reps = 0;
      (this->field16_0x40)._s_0.start_path1 = true;
      (this->field20_0x88)._s_0.on_point = 0;
    }
    local_10 = VVar28;
    if ((this->field16_0x40)._s_0.start_path1 != false) goto LAB_0041dba9;
LAB_0041dcd0:
    if ((this->field16_0x40)._s_0.start_path2 != false) goto LAB_0041dcda;
LAB_0041de00:
    if ((this->field16_0x40)._s_0.start_path3 != false) goto LAB_0041de0a;
LAB_0041df2c:
    if ((this->field16_0x40)._s_0.jump_start != false) goto LAB_0041df32;
  }
  else {
LAB_0041dba9:
    if ((this->field16_0x40)._s_0.start_path2 == false) {
      if (local_8 == (this->field18_0x64)._s_0.get_in_me) {
        pVVar2 = (this->field19_0x74).p_array[0]->points;
        iVar23 = (this->field20_0x88)._s_0.on_point;
        VVar29.z = pVVar2[iVar23].z;
        VVar29.x = pVVar2[iVar23].x;
        VVar11.z = local_1c;
        VVar11.x = local_20;
        VVar28 = Vec2D_Subtract(VVar29,VVar11);
        local_10.z = VVar28.z;
        fVar30 = SQRT(local_10.z * local_10.z + local_10.x * local_10.x);
        if ((this->field17_0x54)._s_0.forgiveness < fVar30) {
          fVar31 = Get_Time();
          if ((this->field17_0x54)._s_0.repeat_time < fVar31) {
            AudioMessage("misn0103.wav");
            bVar21 = IsAlive(&(this->field18_0x64)._s_0.target);
            if (!bVar21) {
              bVar21 = IsAlive(&(this->field18_0x64)._s_0.target2);
              if ((!bVar21) && ((this->field16_0x40)._s_0.lost == false)) {
                pcVar32 = "misn01l1.des";
                (this->field16_0x40)._s_0.lost = true;
                fVar31 = Get_Time();
                FailMission(fVar31 + 5.0,pcVar32);
              }
            }
            fVar31 = Get_Time();
            piVar1 = &(this->field20_0x88)._s_0.num_reps;
            *piVar1 = *piVar1 + 1;
            (this->field17_0x54)._s_0.repeat_time = fVar31 + 15.0;
          }
        }
        pAVar24 = (this->field19_0x74).p_array[0];
        pVVar2 = pAVar24->points;
        iVar23 = (this->field20_0x88)._s_0.on_point;
        VVar4.z = pVVar2[iVar23 + 1].z;
        VVar4.x = pVVar2[iVar23 + 1].x;
        VVar12.z = local_1c;
        VVar12.x = local_20;
        VVar28 = Vec2D_Subtract(VVar4,VVar12);
        fVar31 = local_2c.x * local_2c.x;
        local_2c.z = VVar28.z;
        fVar3 = local_2c.z * local_2c.z;
        local_2c = VVar28;
        if ((SQRT(fVar3 + fVar31) < fVar30) &&
           ((this->field20_0x88)._s_0.on_point = iVar23 + 1, iVar23 + 1 == pAVar24->pointCount + -1)
           ) {
          (this->field20_0x88)._s_0.on_point = 0;
          (this->field16_0x40)._s_0.start_path2 = true;
        }
      }
      goto LAB_0041dcd0;
    }
LAB_0041dcda:
    if ((this->field16_0x40)._s_0.start_path3 == false) {
      pVVar2 = (this->field19_0x74).p_array[1]->points;
      iVar23 = (this->field20_0x88)._s_0.on_point;
      VVar5.z = pVVar2[iVar23].z;
      VVar5.x = pVVar2[iVar23].x;
      VVar13.z = local_1c;
      VVar13.x = local_20;
      VVar28 = Vec2D_Subtract(VVar5,VVar13);
      local_2c.z = VVar28.z;
      fVar30 = SQRT(local_2c.z * local_2c.z + local_2c.x * local_2c.x);
      if ((this->field17_0x54)._s_0.forgiveness < fVar30) {
        fVar31 = Get_Time();
        if ((this->field17_0x54)._s_0.repeat_time < fVar31) {
          AudioMessage("misn0103.wav");
          bVar21 = IsAlive(&(this->field18_0x64)._s_0.target);
          if (!bVar21) {
            bVar21 = IsAlive(&(this->field18_0x64)._s_0.target2);
            if ((!bVar21) && ((this->field16_0x40)._s_0.lost == false)) {
              pcVar32 = "misn01l1.des";
              (this->field16_0x40)._s_0.lost = true;
              fVar31 = Get_Time();
              FailMission(fVar31 + 5.0,pcVar32);
            }
          }
          fVar31 = Get_Time();
          piVar1 = &(this->field20_0x88)._s_0.num_reps;
          *piVar1 = *piVar1 + 1;
          (this->field17_0x54)._s_0.repeat_time = fVar31 + 15.0;
        }
      }
      pAVar24 = (this->field19_0x74).p_array[1];
      pVVar2 = pAVar24->points;
      iVar23 = (this->field20_0x88)._s_0.on_point;
      VVar6.z = pVVar2[iVar23 + 1].z;
      VVar6.x = pVVar2[iVar23 + 1].x;
      VVar14.z = local_1c;
      VVar14.x = local_20;
      VVar29 = Vec2D_Subtract(VVar6,VVar14);
      local_2c.x = VVar28.x;
      fVar31 = local_2c.x * local_2c.x;
      local_2c.z = VVar29.z;
      fVar3 = local_2c.z * local_2c.z;
      local_2c = VVar29;
      if ((SQRT(fVar3 + fVar31) < fVar30) &&
         ((this->field20_0x88)._s_0.on_point = iVar23 + 1, iVar23 + 1 == pAVar24->pointCount + -1))
      {
        (this->field16_0x40)._s_0.start_path3 = true;
        AudioMessage("misn0104.wav");
        (this->field20_0x88)._s_0.on_point = 0;
      }
      goto LAB_0041de00;
    }
LAB_0041de0a:
    if ((this->field16_0x40)._s_0.jump_start == false) {
      pVVar2 = (this->field19_0x74).p_array[2]->points;
      iVar23 = (this->field20_0x88)._s_0.on_point;
      VVar7.z = pVVar2[iVar23].z;
      VVar7.x = pVVar2[iVar23].x;
      VVar15.z = local_1c;
      VVar15.x = local_20;
      VVar28 = Vec2D_Subtract(VVar7,VVar15);
      local_2c.z = VVar28.z;
      fVar30 = SQRT(local_2c.z * local_2c.z + local_2c.x * local_2c.x);
      if ((this->field17_0x54)._s_0.forgiveness < fVar30) {
        fVar31 = Get_Time();
        if ((this->field17_0x54)._s_0.repeat_time < fVar31) {
          AudioMessage("misn0103.wav");
          bVar21 = IsAlive(&(this->field18_0x64)._s_0.target);
          if (!bVar21) {
            bVar21 = IsAlive(&(this->field18_0x64)._s_0.target2);
            if ((!bVar21) && ((this->field16_0x40)._s_0.lost == false)) {
              pcVar32 = "misn01l1.des";
              (this->field16_0x40)._s_0.lost = true;
              fVar31 = Get_Time();
              FailMission(fVar31 + 5.0,pcVar32);
            }
          }
          fVar31 = Get_Time();
          piVar1 = &(this->field20_0x88)._s_0.num_reps;
          *piVar1 = *piVar1 + 1;
          (this->field17_0x54)._s_0.repeat_time = fVar31 + 15.0;
        }
      }
      pAVar24 = (this->field19_0x74).p_array[2];
      pVVar2 = pAVar24->points;
      iVar23 = (this->field20_0x88)._s_0.on_point;
      VVar8.z = pVVar2[iVar23 + 1].z;
      VVar8.x = pVVar2[iVar23 + 1].x;
      VVar16.z = local_1c;
      VVar16.x = local_20;
      VVar29 = Vec2D_Subtract(VVar8,VVar16);
      local_2c.x = VVar28.x;
      fVar31 = local_2c.x * local_2c.x;
      local_2c.z = VVar29.z;
      fVar3 = local_2c.z * local_2c.z;
      local_2c = VVar29;
      if ((SQRT(fVar3 + fVar31) < fVar30) &&
         ((this->field20_0x88)._s_0.on_point = iVar23 + 1, iVar23 + 1 == pAVar24->pointCount + -1))
      {
        (this->field16_0x40)._s_0.jump_start = true;
        fVar30 = Get_Time();
        (this->field17_0x54)._s_0.jump_done = fVar30 + 8.0;
      }
      goto LAB_0041df2c;
    }
LAB_0041df32:
    if ((this->field16_0x40)._s_0.hint1 == false) {
      fVar30 = Get_Time();
      if ((this->field17_0x54)._s_0.jump_done < fVar30) {
        fVar30 = Get_Time();
        (this->field17_0x54)._s_0.repeat_time = fVar30 + 45.0;
        AudioMessage("misn0105.wav");
        (this->field17_0x54)._s_0.forgiveness = (this->field17_0x54)._s_0.forgiveness * 1.5;
        AudioMessage("misn0107.wav");
        (this->field16_0x40)._s_0.hint1 = true;
      }
    }
  }
  if ((this->field16_0x40)._s_0.start_path4 == false) {
    VVar17.z = local_1c;
    VVar17.x = local_20;
    VVar28 = Vec2D_Subtract(*((this->field19_0x74)._s_0.p4)->points,VVar17);
    local_2c.z = VVar28.z;
    if (SQRT(local_2c.z * local_2c.z + local_2c.x * local_2c.x) <
        (this->field17_0x54)._s_0.forgiveness) {
      (this->field20_0x88)._s_0.num_reps = 0;
      (this->field17_0x54)._s_0.repeat_time = 0.0;
      (this->field20_0x88)._s_0.on_point = 0;
      (this->field16_0x40)._s_0.start_path4 = true;
      if (local_8 != (this->field18_0x64)._s_0.get_in_me) {
        AudioMessage("misn0122.wav");
      }
    }
    local_2c = VVar28;
    if ((this->field16_0x40)._s_0.start_path4 != false) goto LAB_0041dff2;
LAB_0041e0f9:
    if ((this->field16_0x40)._s_0.combat_start == false) goto LAB_0041e16b;
  }
  else {
LAB_0041dff2:
    if ((this->field16_0x40)._s_0.combat_start == false) {
      pVVar2 = (this->field19_0x74).p_array[3]->points;
      iVar23 = (this->field20_0x88)._s_0.on_point;
      VVar9.z = pVVar2[iVar23].z;
      VVar9.x = pVVar2[iVar23].x;
      VVar18.z = local_1c;
      VVar18.x = local_20;
      VVar28 = Vec2D_Subtract(VVar9,VVar18);
      local_2c.z = VVar28.z;
      fVar30 = SQRT(local_2c.z * local_2c.z + local_2c.x * local_2c.x);
      if ((this->field17_0x54)._s_0.forgiveness < fVar30) {
        fVar31 = Get_Time();
        if ((this->field17_0x54)._s_0.repeat_time < fVar31) {
          AudioMessage("misn0108.wav");
          fVar31 = Get_Time();
          piVar1 = &(this->field20_0x88)._s_0.num_reps;
          *piVar1 = *piVar1 + 1;
          (this->field17_0x54)._s_0.repeat_time = fVar31 + 15.0;
        }
      }
      pAVar24 = (this->field19_0x74).p_array[3];
      pVVar2 = pAVar24->points;
      iVar23 = (this->field20_0x88)._s_0.on_point;
      VVar10.z = pVVar2[iVar23 + 1].z;
      VVar10.x = pVVar2[iVar23 + 1].x;
      VVar19.z = local_1c;
      VVar19.x = local_20;
      VVar29 = Vec2D_Subtract(VVar10,VVar19);
      local_2c.x = VVar28.x;
      local_2c.z = VVar29.z;
      if ((SQRT(local_2c.z * local_2c.z + local_2c.x * local_2c.x) < fVar30) &&
         ((this->field20_0x88)._s_0.on_point = iVar23 + 1, iVar23 + 1 == pAVar24->pointCount + -1))
      {
        cockpitTimer.active = false;
        iVar23 = (this->field18_0x64)._s_0.target;
        (this->field16_0x40)._s_0.combat_start = true;
        SetObjectiveOn(iVar23);
        SetObjectiveName((this->field18_0x64)._s_0.target,"Combat Training");
        AudioMessage("misn0109.wav");
      }
      goto LAB_0041e0f9;
    }
  }
  if ((this->field16_0x40)._s_0.hint2 == false) {
    bVar21 = IsAlive(&(this->field18_0x64)._s_0.target);
    if (bVar21) {
      pVVar26 = (VECTOR_3D *)(**(code **)(pGVar20->_padding_ + 0xc))();
      pVVar27 = (VECTOR_3D *)(**(code **)(pGVar25->_padding_ + 0xc))();
      fVar30 = Dist3D_Squared(*pVVar27,*pVVar26);
      if (fVar30 < 10000.0) {
        CockpitTimer::HideTimer(&cockpitTimer);
        AudioMessage("misn0111.wav");
        (this->field16_0x40)._s_0.hint2 = true;
      }
    }
  }
LAB_0041e16b:
  if ((this->field16_0x40)._s_0.combat_start2 == false) {
    bVar21 = IsAlive(&(this->field18_0x64)._s_0.target);
    if (!bVar21) {
      piVar1 = &(this->field18_0x64)._s_0.target2;
      bVar21 = IsAlive(piVar1);
      if (bVar21) {
        SetObjectiveOn(*piVar1);
        SetObjectiveName(*piVar1,"Combat Training 2");
        AudioMessage("misn0113.wav");
        (this->field16_0x40)._s_0.combat_start2 = true;
      }
    }
  }
  if ((this->field16_0x40)._s_0.done_message == false) {
    bVar21 = IsAlive(&(this->field18_0x64)._s_0.target);
    if (!bVar21) {
      bVar21 = IsAlive(&(this->field18_0x64)._s_0.target2);
      if (!bVar21) {
        AudioMessage("misn0121.wav");
        (this->field16_0x40)._s_0.done_message = true;
        pcVar32 = "misn01w1.des";
        fVar30 = Get_Time();
        SucceedMission(fVar30 + 10.0,pcVar32);
      }
    }
  }
  if ((4 < (this->field20_0x88)._s_0.num_reps) && ((this->field16_0x40)._s_0.lost == false)) {
    (this->field17_0x54)._s_0.repeat_time = 99999.0;
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"misn0102.otf",DisplayInterface::colorRed,8.0);
    AudioMessage("misn0123.wav");
    pcVar32 = "misn01l1.des";
    fVar30 = Get_Time();
    FailMission(fVar30 + 10.0,pcVar32);
    (this->field20_0x88)._s_0.num_reps = 0;
  }
  return;
}
