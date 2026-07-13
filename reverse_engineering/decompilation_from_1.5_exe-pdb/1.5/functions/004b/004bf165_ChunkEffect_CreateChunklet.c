/*
 * Entry: 004bf165
 * Name: ChunkEffect::CreateChunklet
 * Namespace: ChunkEffect
 * Signature: void CreateChunklet(ChunkEffect * this, VECTOR_3D param_1, VECTOR_3D param_2, bool param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
ChunkEffect::CreateChunklet(ChunkEffect *this,VECTOR_3D param_1,VECTOR_3D param_2,bool param_3)

{
  float fVar1;
  _OBJ76 *p_Var2;
  _OBJ76 *p_Var3;
  uint uVar4;
  MAT_3D *pMVar5;
  int iVar6;
  float *pfVar7;
  BBOX *pBVar8;
  BBOX *pBVar9;
  float fVar10;
  float fVar11;
  MAT_3D local_90;
  float local_50 [16];
  ChunkEffect *local_10;
  Chunk *local_c;
  _OBJ76 *local_8;
  
  iVar6 = this->chunkCount;
  if (iVar6 < 0x400) {
    this->chunkCount = iVar6 + 1;
    local_c = this->chunkList + iVar6;
    local_10 = this;
    local_8 = create_obj(this->ent->obj76,".\\fun3d\\ChunkEffect.cpp");
    local_8->class_id = CLASS_ID_CHUNK;
    local_8->flags = -(uint)param_3 & 8;
    uVar4 = (Rand_Counter + 1U & 0xff) + 1;
    Rand_Counter = uVar4 & 0xff;
    fVar1 = Pseudo_Rand_Number[Rand_Counter];
    fVar11 = *(float *)(&DAT_00c9021c + uVar4 * 4) * 0.15707964;
    fVar10 = rand<float>(6.2831855);
    pMVar5 = Build_Position_Rotation_Matrix
                       (&local_90,fVar1 * 1.5707964,fVar10,fVar11,param_1.x,param_1.y,param_1.z);
    pfVar7 = local_50;
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *pfVar7 = pMVar5->right_x;
      pMVar5 = (MAT_3D *)&pMVar5->right_y;
      pfVar7 = pfVar7 + 1;
    }
    pfVar7 = local_50;
    pMVar5 = &local_8->transform;
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      pMVar5->right_x = *pfVar7;
      pfVar7 = pfVar7 + 1;
      pMVar5 = (MAT_3D *)&pMVar5->right_y;
    }
    iVar6 = rand();
    p_Var3 = local_8;
    p_Var2 = local_10->chunkletList[iVar6 % local_10->chunkletCount];
    GeoCache_Clone(p_Var2,local_8);
    Texture_Clone(p_Var2,p_Var3);
    (p_Var3->bSphere).origin.x = (p_Var2->bSphere).origin.x;
    (p_Var3->bSphere).origin.y = (p_Var2->bSphere).origin.y;
    (p_Var3->bSphere).origin.z = (p_Var2->bSphere).origin.z;
    (p_Var3->bSphere).radius = (p_Var2->bSphere).radius;
    pBVar8 = &p_Var2->bBox;
    pBVar9 = &local_8->bBox;
    for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
      (pBVar9->min).x = (pBVar8->min).x;
      pBVar8 = (BBOX *)&(pBVar8->min).y;
      pBVar9 = (BBOX *)&(pBVar9->min).y;
    }
    local_c->timer = 0.0;
    local_c->obj = local_8;
    Rand_Counter = Rand_Counter + 1U & 0xff;
    (local_c->veloc).x = Pseudo_Rand_Number[Rand_Counter] * 10.0 + param_2.x;
    Rand_Counter = Rand_Counter + 1U & 0xff;
    (local_c->veloc).y = Pseudo_Rand_Number[Rand_Counter] * 10.0 + param_2.y + 5.0;
    Rand_Counter = Rand_Counter + 1U & 0xff;
    (local_c->veloc).z = Pseudo_Rand_Number[Rand_Counter] * 10.0 + param_2.z;
    Rand_Counter = Rand_Counter + 1U & 0xff;
    (local_c->omega).x = Pseudo_Rand_Number[Rand_Counter] * 5.0;
    Rand_Counter = Rand_Counter + 1U & 0xff;
    (local_c->omega).y = Pseudo_Rand_Number[Rand_Counter] * 5.0;
    Rand_Counter = Rand_Counter + 1U & 0xff;
    (local_c->omega).z = Pseudo_Rand_Number[Rand_Counter] * 5.0;
  }
  return;
}
