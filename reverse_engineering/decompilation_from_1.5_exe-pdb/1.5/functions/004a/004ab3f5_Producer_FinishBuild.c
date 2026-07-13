/*
 * Entry: 004ab3f5
 * Name: Producer::FinishBuild
 * Namespace: Producer
 * Signature: GameObject * FinishBuild(Producer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall Producer::FinishBuild(Producer *this)

{
  uint *puVar1;
  GameObjectClass *this_00;
  VECTOR_3D VVar2;
  undefined8 uVar3;
  uint uVar4;
  MAT_3D *pMVar5;
  VECTOR_3D *pVVar6;
  GameObject *this_01;
  BBOX *pBVar7;
  float *pfVar8;
  uint extraout_EAX;
  ushort *puVar9;
  AiMission *pAVar10;
  int iVar11;
  float fVar12;
  MAT_3D *pMVar13;
  MAT_3D local_f0;
  MAT_3D local_b0;
  undefined1 local_70 [12];
  undefined1 local_64 [20];
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  undefined4 local_38;
  float local_34;
  float local_30;
  undefined4 local_2c;
  float local_28;
  undefined1 local_24 [12];
  float local_18;
  float local_14;
  float local_10;
  uint local_c;
  float local_8;
  
  this->_padding_ = -1;
  (**(code **)(this->_padding_ + 0xa8))(&local_b0);
  this_00 = this->buildClass;
  if ((this_00->class_id == CLASS_ID_STRUCTURE1) || (this_00->sig == 0x54555252)) {
    this_01 = GameObjectClass::Build(this_00,&local_b0,this->_padding_,0,-1,(char *)0x0);
    pBVar7 = GameObjectClass::GetBoundingBox(this->buildClass);
    local_64._16_4_ = (pBVar7->min).x;
    local_50 = 0.0;
    local_4c = (pBVar7->min).z;
    local_48 = (pBVar7->min).x;
    local_44 = 0.0;
    local_40 = (pBVar7->max).z;
    local_3c = (pBVar7->max).x;
    local_38 = 0;
    local_34 = (pBVar7->max).z;
    local_30 = (pBVar7->max).x;
    local_2c = 0;
    local_28 = (pBVar7->min).z;
    Vector_Transform((VECTOR_3D *)(local_64 + 0x10),(VECTOR_3D *)(local_64 + 0x10),4,&local_b0);
    local_18 = NAN;
    local_8 = NAN;
    local_10 = -0.0;
    local_14 = -0.0;
    pfVar8 = &local_4c;
    local_c = 4;
    do {
      local_70._4_8_ = (undefined8)(pfVar8[-2] * Terrain.Grid_Scale + (float)Float2Int);
      local_24._4_8_ = (undefined8)(*pfVar8 * Terrain.Grid_Scale + (float)Float2Int);
      uVar3 = local_24._4_8_;
      if ((int)local_70._4_4_ < (int)local_18) {
        local_18 = (float)local_70._4_4_;
      }
      if ((int)local_10 < (int)local_70._4_4_) {
        local_10 = (float)local_70._4_4_;
      }
      if ((int)local_24._4_4_ < (int)local_8) {
        local_8 = (float)local_24._4_4_;
      }
      if ((int)local_14 < (int)local_24._4_4_) {
        local_14 = (float)local_24._4_4_;
      }
      pfVar8 = pfVar8 + 3;
      local_c = local_c + -1;
    } while (local_c != 0);
    local_24._4_8_ = uVar3;
    _ftol2_sse();
    if ((int)extraout_EAX < 0) {
      local_c = 0;
    }
    else if ((int)extraout_EAX < 0x1000) {
      local_c = extraout_EAX & 0xffff;
    }
    else {
      local_c = 0xfff;
    }
    local_14 = (float)((int)local_14 + 1);
    if ((int)local_8 <= (int)local_14) {
      local_10 = (float)((int)local_10 + 1);
      do {
        fVar12 = local_18;
        if ((int)local_18 <= (int)local_10) {
          do {
            puVar9 = GetZonePtr((int)fVar12,(int)local_8);
            fVar12 = (float)((int)fVar12 + 1);
            *puVar9 = *puVar9 & 0xf000 | (ushort)local_c;
          } while ((int)fVar12 <= (int)local_10);
        }
        local_8 = (float)((int)local_8 + 1);
      } while ((int)local_8 <= (int)local_14);
    }
  }
  else {
    uVar4 = Rand_Counter + 1U & 0xff;
    Rand_Counter = uVar4 + 1 & 0xff;
    pMVar5 = Build_Pitch_Yaw_Matrix
                       ((MAT_3D *)local_64,Pseudo_Rand_Number[Rand_Counter] * 0.25,
                        Pseudo_Rand_Number[uVar4]);
    pMVar13 = &local_f0;
    for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
      pMVar13->right_x = pMVar5->right_x;
      pMVar5 = (MAT_3D *)&pMVar5->right_y;
      pMVar13 = (MAT_3D *)&pMVar13->right_y;
    }
    pMVar5 = Matrix_Multiply((MAT_3D *)local_64,&local_f0,&local_b0);
    pMVar13 = &local_b0;
    for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
      pMVar13->right_x = pMVar5->right_x;
      pMVar5 = (MAT_3D *)&pMVar5->right_y;
      pMVar13 = (MAT_3D *)&pMVar13->right_y;
    }
    local_24._0_4_ = local_b0.front_x;
    VVar2.y = local_b0.front_y;
    VVar2.x = local_b0.front_x;
    VVar2.z = local_b0.front_z;
    pVVar6 = ScaleVector((VECTOR_3D *)local_70,25.0,VVar2);
    iVar11 = this->_padding_;
    local_24._0_4_ = pVVar6->x;
    local_24._4_8_ = *(undefined8 *)&pVVar6->y;
    local_b0.right_x = *(float *)(iVar11 + 0x20);
    local_b0.right_y = *(float *)(iVar11 + 0x24);
    local_b0.right_z = *(float *)(iVar11 + 0x28);
    local_b0.up_x = *(float *)(iVar11 + 0x2c);
    local_b0.up_y = *(float *)(iVar11 + 0x30);
    local_b0.up_z = *(float *)(iVar11 + 0x34);
    local_b0.front_x = *(float *)(iVar11 + 0x38);
    local_b0.front_y = *(float *)(iVar11 + 0x3c);
    local_b0.front_z = *(float *)(iVar11 + 0x40);
    this_01 = GameObjectClass::Build(this->buildClass,&local_b0,this->_padding_,0,-1,(char *)0x0);
    GameObject::SetVelocity(this_01,(VECTOR_3D *)local_24);
    if (this->buildClass->class_id == CLASS_ID_POWERUP) {
      GameObject::SetOwner(this_01,(GameObject *)this);
      puVar1 = (uint *)(this_01[1]._padding_ + 0x10c);
      *puVar1 = *puVar1 | 0xc;
    }
  }
  iVar11 = Net_IsNetGame();
  if (iVar11 != 0) {
    DistributedObject::SetLocal((DistributedObject *)&this_01->_padding_);
  }
  pAVar10 = AiMission::GetCurrent();
  (**(code **)(pAVar10->_padding_ + 0x18))(this_01);
  DoAudioNew((char *)(this->_padding_ + 0x40c),(_OBJ76 *)this->_padding_,(GAS_CTRL *)0x0);
  this->buildClass = (GameObjectClass *)0x0;
  return this_01;
}
