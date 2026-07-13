/*
 * Entry: 005327ca
 * Name: ObjectLobber::Simulate
 * Namespace: ObjectLobber
 * Signature: void Simulate(ObjectLobber * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ObjectLobber::Simulate(ObjectLobber *this,float param_1)

{
  uint *puVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  VECTOR_3D VVar6;
  VECTOR_3D VVar7;
  VECTOR_3D VVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  int iVar11;
  VECTOR_3D *pVVar12;
  MAT_3D *pMVar13;
  GameObject *pGVar14;
  GameObject *pGVar15;
  AiMission *pAVar16;
  VECTOR_3D *unaff_ESI;
  float *pfVar17;
  VECTOR_3D *unaff_EDI;
  float *pfVar18;
  MAT_3D local_f8;
  VECTOR_3D local_b8;
  MAT_3D local_ac;
  float local_6c [4];
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  double local_44;
  double local_3c;
  double local_34;
  VECTOR_3D local_2c;
  VECTOR_3D local_20;
  GameObject *local_14;
  VECTOR_3D local_10;
  
  fVar3 = param_1 + this->shotTimer;
  this->shotTimer = fVar3;
  if (this->triggered == false) {
    if (0.0 < fVar3) {
      this->shotTimer = 0.0;
    }
  }
  else {
    if ((this->target != (VECTOR_3D *)0x0) && (0.0 < fVar3)) {
      iVar11 = this->objectClass->categoryMin;
      iVar2 = this->objectClass->categoryMax;
      if ((iVar11 == -1) ||
         ((iVar2 == -1 ||
          (iVar11 = Team::FirstEmptySlot(this->carrier->teamList,iVar11,iVar2), -1 < iVar11)))) {
        pVVar12 = this->target;
        fVar3 = pVVar12->x - (float)*(double *)&this->_padding_;
        fVar4 = pVVar12->y - (float)*(double *)&this->_padding_;
        fVar5 = pVVar12->z - (float)*(double *)&this->_padding_;
        param_1 = SQRT(SQRT(fVar5 * fVar5 + fVar4 * fVar4 + fVar3 * fVar3) * 9.8) + 20.0;
        if (*(float *)(this->_padding_ + 0x7c) < param_1) {
          param_1 = *(float *)(this->_padding_ + 0x7c);
        }
        local_10.x = (float)*(double *)&this->_padding_;
        local_10.y = (float)*(double *)&this->_padding_;
        local_10.z = (float)*(double *)&this->_padding_;
        uVar9 = pVVar12->y;
        uVar10 = pVVar12->z;
        VVar8.y = (float)uVar10;
        VVar8.x = (float)uVar9;
        VVar6.y = local_10.z;
        VVar6.x = local_10.y;
        VVar6.z = pVVar12->x;
        VVar8.z = param_1;
        pVVar12 = CalculateArc((VECTOR_3D *)local_10.x,VVar6,VVar8,(float)unaff_EDI);
        local_2c.x = pVVar12->x;
        local_2c.y = pVVar12->y;
        local_2c.z = pVVar12->z;
        pVVar12 = Vector_Unrotate(&local_20,&local_2c,(MAT_3D *)&this->_padding_);
        iVar11 = this->_padding_;
        local_2c.x = pVVar12->x;
        local_2c.y = pVVar12->y;
        local_2c.z = pVVar12->z;
        local_20.x = (float)*(double *)(iVar11 + 0x48);
        local_20.y = (float)*(double *)(iVar11 + 0x50);
        local_20.z = (float)*(double *)(iVar11 + 0x58);
        local_10.x = local_20.x;
        local_10.y = local_20.y;
        local_10.z = local_20.z;
        pMVar13 = Build_Directinal_Matrix(&local_f8,unaff_EDI,unaff_ESI);
        pfVar17 = local_6c;
        for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
          *pfVar17 = pMVar13->right_x;
          pMVar13 = (MAT_3D *)&pMVar13->right_y;
          pfVar17 = pfVar17 + 1;
        }
        pfVar17 = local_6c;
        pfVar18 = (float *)(this->_padding_ + 0x20);
        for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
          *pfVar18 = *pfVar17;
          pfVar17 = pfVar17 + 1;
          pfVar18 = pfVar18 + 1;
        }
        DoAudioNew((char *)(this->_padding_ + 0x58),(_OBJ76 *)this->_padding_,(GAS_CTRL *)0x0);
        pMVar13 = Matrix_Multiply(&local_f8,(MAT_3D *)(this->_padding_ + 0x20),
                                  (MAT_3D *)&this->_padding_);
        pfVar17 = local_6c;
        for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
          *pfVar17 = pMVar13->right_x;
          pMVar13 = (MAT_3D *)&pMVar13->right_y;
          pfVar17 = pfVar17 + 1;
        }
        local_ac.right_x = local_6c[0];
        local_ac.right_y = local_6c[1];
        local_ac.right_z = local_6c[2];
        local_ac.up_x = local_54;
        local_ac.up_y = local_50;
        local_ac.up_z = local_4c;
        local_ac.front_x = -local_6c[3];
        local_ac.front_y = -local_5c;
        local_ac.front_z = -local_58;
        local_ac.posit_x = local_44;
        local_ac.posit_y = local_3c;
        local_ac.posit_z = local_34;
        pGVar14 = GameObjectClass::Build
                            (this->objectClass,&local_ac,*(ushort *)(this->_padding_ + 0x16) & 0xf,0
                             ,-1,(char *)0x0);
        if (pGVar14 != (GameObject *)0x0) {
          if (this->_padding_ == 0) {
            pGVar15 = (GameObject *)0x0;
          }
          else {
            pGVar15 = *(GameObject **)(this->_padding_ + 0xb4);
          }
          local_14 = pGVar14;
          GameObject::SetOwner(pGVar14,pGVar15);
          iVar11 = Net_IsNetGame();
          if (iVar11 != 0) {
            DistributedObject::SetLocal((DistributedObject *)&pGVar14->_padding_);
          }
          if (this->objectClass->class_id == CLASS_ID_POWERUP) {
            puVar1 = (uint *)(pGVar14[1]._padding_ + 0x10c);
            *puVar1 = *puVar1 | 0xc;
            GameObject::SetCommand(pGVar14,CMD_GO,this->target,0);
          }
          pAVar16 = AiMission::GetCurrent();
          (**(code **)(pAVar16->_padding_ + 0x18))(pGVar14);
          local_10.x = local_54;
          local_10.y = local_50;
          local_10.z = local_4c;
          VVar7.y = local_50;
          VVar7.x = local_54;
          VVar7.z = local_4c;
          pVVar12 = ScaleVector(&local_b8,param_1,VVar7);
          pGVar14 = local_14;
          local_10.x = pVVar12->x;
          local_10.y = pVVar12->y;
          local_10.z = pVVar12->z;
          GameObject::SetVelocity(local_14,&local_10);
          (**(code **)(pGVar14->_padding_ + 0x3c))(this->shotTimer);
        }
        this->shotTimer = this->shotTimer - *(float *)(this->_padding_ + 0x78);
      }
    }
    this->triggered = false;
  }
  return;
}
