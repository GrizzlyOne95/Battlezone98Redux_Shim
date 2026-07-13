/*
 * Entry: 004bf869
 * Name: CockpitRadar::Simulate
 * Namespace: CockpitRadar
 * Signature: void Simulate(CockpitRadar * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CockpitRadar::Simulate(CockpitRadar *this,float param_1)

{
  float fVar1;
  Scanner *pSVar2;
  _OBJ76 *p_Var3;
  int iVar4;
  VECTOR_3D VVar5;
  VECTOR_3D VVar6;
  float fVar7;
  uint6 uVar8;
  float fVar9;
  float fVar10;
  DWORD DVar11;
  long lVar12;
  float *pfVar13;
  GameObject *pGVar14;
  int extraout_EAX;
  VECTOR_3D *pVVar15;
  ushort *puVar16;
  uint uVar17;
  int iVar18;
  float unaff_EDI;
  float10 extraout_ST0;
  float10 fVar19;
  tagPOINT tVar20;
  double dVar21;
  VECTOR_3D local_9c;
  VECTOR_3D local_90;
  float local_84;
  float local_80;
  float local_7c;
  VECTOR_3D local_78;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  undefined8 local_3c;
  VECTOR_3D local_34;
  int local_28;
  int iStack_24;
  RADAR_MESH *local_20;
  undefined8 local_1c;
  uint local_14;
  float local_10;
  float local_c;
  float local_8;
  
  pGVar14 = GameObject::userObject;
  if (((useDisplayInterface != 0) && (hudFlags != 0)) &&
     (this->userObj = GameObject::userObject, pGVar14 != (GameObject *)0x0)) {
    pSVar2 = pGVar14->scanner;
    this->scanner = pSVar2;
    if (pSVar2 != (Scanner *)0x0) {
      if ((pSVar2->active != false) && (0.0 < pSVar2->period)) {
        StartGASEvent("ping.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0);
        this->pingFrame = 14.0;
      }
      fVar1 = this->pingFrame - param_1 * 20.0;
      this->pingFrame = fVar1;
      if (fVar1 < 0.0) {
        this->pingFrame = 0.0;
      }
      if (avgFrameTime < 0x39) {
        if (avgFrameTime < 0x28) {
          this->timeBetweenSimulations = 0;
        }
      }
      else {
        this->timeBetweenSimulations = 200;
      }
      DVar11 = timeGetTime();
      if (DVar11 - this->timeSimulated < (uint)this->timeBetweenSimulations) {
        this->simulated = true;
      }
      else {
        DVar11 = timeGetTime();
        this->timeSimulated = DVar11;
        fVar1 = this->scanner->range;
        this->range = fVar1;
        this->rangeSq = fVar1 * fVar1;
        lVar12 = (**(code **)(this->userObj->_padding_ + 4))();
        this->userTeam = lVar12;
        pfVar13 = (float *)(**(code **)(this->userObj->_padding_ + 0xc))();
        pGVar14 = this->userObj;
        (this->userPos).x = *pfVar13;
        (this->userPos).y = pfVar13[1];
        (this->userPos).z = pfVar13[2];
        pGVar14 = GameObject::GetObj(pGVar14->targetHandle);
        this->targetObj = pGVar14;
        p_Var3 = this->userObj->obj;
        local_10 = (p_Var3->transform).front_x;
        local_c = (p_Var3->transform).front_y;
        local_8 = (p_Var3->transform).front_z;
        dVar21 = rsqrt((double)(local_10 * local_10 + local_8 * local_8));
        pGVar14 = this->userObj;
        fVar1 = local_10 * (float)dVar21;
        fVar7 = local_8 * (float)dVar21;
        (this->mat).right_x = fVar7;
        (this->mat).right_y = 0.0;
        (this->mat).right_z = -fVar1;
        fVar10 = RADAR_SIN;
        (this->mat).up_x = RADAR_SIN * fVar1;
        fVar9 = RADAR_COS;
        (this->mat).up_y = RADAR_COS;
        (this->mat).up_z = fVar10 * fVar7;
        (this->mat).front_x = fVar9 * fVar1;
        (this->mat).front_y = -fVar10;
        (this->mat).front_z = fVar7 * fVar9;
        (this->mat).posit_x = 0.0;
        (this->mat).posit_y = 0.0;
        (this->mat).posit_z = 0.0;
        pfVar13 = (float *)(**(code **)(pGVar14->_padding_ + 0xc))();
        local_48 = *pfVar13;
        local_44 = pfVar13[1];
        fVar1 = (float)Float2Int;
        local_40 = pfVar13[2];
        local_28 = SUB84((double)(this->range * Terrain.Grid_Scale + fVar1),0);
        local_1c._0_4_ = SUB84((double)(local_48 * Terrain.Grid_Scale + fVar1),0);
        uVar17 = (int)local_1c - local_28 & 0xfffffffe;
        local_3c = (double)(fVar1 + local_40 * Terrain.Grid_Scale);
        local_14 = (int)local_3c - local_28 & 0xfffffffe;
        iStack_24 = (int)((((int)local_1c + local_28 & 0xfffffffeU) - uVar17) + 2) / 2;
        (this->radarMesh).dx = iStack_24;
        local_1c._4_4_ = (int)((((int)local_3c + local_28 & 0xfffffffeU) - local_14) + 2) / 2;
        (this->radarMesh).dy = local_1c._4_4_;
        (this->radarMesh).wx = uVar17;
        (this->radarMesh).wz = local_14;
        _ftol2_sse();
        fVar19 = extraout_ST0 + extraout_ST0;
        (this->radarMesh).color = RADAR_PING[extraout_EAX].color;
        local_6c = (float)((float10)(this->mat).right_x * fVar19);
        local_68 = (float)((float10)(this->mat).up_x * fVar19);
        local_64 = (float)((float10)(this->mat).front_x * fVar19);
        local_84 = (this->mat).right_y;
        local_80 = (this->mat).up_y;
        local_7c = (this->mat).front_y;
        local_60 = (float)(fVar19 * (float10)(this->mat).right_z);
        local_5c = (float)(fVar19 * (float10)(this->mat).up_z);
        local_58 = (float)(fVar19 * (float10)(this->mat).front_z);
        local_34.x = (float)((float10)(int)uVar17 * extraout_ST0 - (float10)local_48);
        local_34.y = 0.0;
        local_34.z = (float)(extraout_ST0 * (float10)(int)local_14 - (float10)local_40);
        pVVar15 = Vector_Unrotate(&local_78,&local_34,&this->mat);
        local_34.x = pVVar15->x;
        local_34.y = pVVar15->y;
        local_34.z = pVVar15->z;
        memset(&this->radarMesh,0,local_1c._4_4_ * iStack_24 * 8);
        iVar4 = (this->radarMesh).dy;
        local_1c = CONCAT44(iVar4,(int)local_1c);
        local_20 = &this->radarMesh;
        while (0 < iVar4) {
          param_1 = (float)(this->radarMesh).wx;
          iStack_24 = (this->radarMesh).dx;
          pVVar15 = &local_34;
          while( true ) {
            local_54 = pVVar15->x;
            local_50 = pVVar15->y;
            local_4c = pVVar15->z;
            if (iStack_24 < 1) break;
            puVar16 = GetZonePtr((int)param_1,local_14);
            uVar8 = CONCAT24(*puVar16,(int)local_3c) & 0xfffffffffff;
            local_3c = (double)(ulonglong)uVar8;
            dVar21 = local_3c;
            local_3c._4_4_ = (uint)(ushort)(uVar8 >> 0x20);
            fVar1 = (float)local_3c._4_4_;
            VVar5.y = local_50;
            VVar5.x = local_54;
            VVar5.z = local_4c;
            VVar6.y = local_80;
            VVar6.x = local_84;
            VVar6.z = local_7c;
            local_3c = dVar21;
            pVVar15 = AddMultVectors(&local_9c,VVar5,fVar1 * 0.1 - local_44,VVar6);
            local_10 = pVVar15->x;
            local_c = pVVar15->y;
            local_8 = pVVar15->z;
            if (local_10 * local_10 + local_8 * local_8 + local_c * local_c < this->rangeSq) {
              tVar20 = ConvertPos((VECTOR_3D *)this->range,unaff_EDI);
              iVar4 = (DisplayInterface::currentBuffer->Pane).y1;
              iVar18 = tVar20.y;
              if (iVar4 < tVar20.y) {
                iVar18 = iVar4;
              }
              local_20->mesh[0].x = tVar20.x;
              local_20->mesh[0].y = iVar18;
            }
            local_20 = (RADAR_MESH *)(local_20->mesh + 1);
            param_1 = (float)((int)param_1 + 2);
            iStack_24 = iStack_24 + -1;
            local_90.x = local_54 + local_6c;
            pVVar15 = &local_90;
            local_90.y = local_50 + local_68;
            local_90.z = local_4c + local_64;
          }
          local_14 = local_14 + 2;
          iVar4 = local_1c._4_4_ + -1;
          local_1c = CONCAT44(iVar4,(int)local_1c);
          local_78.x = local_34.x + local_60;
          local_78.y = local_34.y + local_5c;
          local_78.z = local_34.z + local_58;
          local_34.x = local_34.x + local_60;
          local_34.y = local_34.y + local_5c;
          local_34.z = local_34.z + local_58;
        }
        this->simulated = true;
        if ((TEXTURE_CENTER.x != RADAR_CENTER.x) || (TEXTURE_CENTER.y != RADAR_CENTER.y)) {
          TEXTURE_CENTER.x = RADAR_CENTER.x;
          TEXTURE_CENTER.y = RADAR_CENTER.y;
        }
      }
    }
  }
  return;
}
