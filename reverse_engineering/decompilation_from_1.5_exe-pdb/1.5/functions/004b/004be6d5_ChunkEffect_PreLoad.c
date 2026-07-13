/*
 * Entry: 004be6d5
 * Name: ChunkEffect::PreLoad
 * Namespace: ChunkEffect
 * Signature: void PreLoad(ChunkEffect * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall ChunkEffect::PreLoad(ChunkEffect *this)

{
  int *piVar1;
  bool bVar2;
  longlong lVar3;
  int iVar4;
  _OBJ76 *p_Var5;
  tagENTITY *ptVar6;
  _OBJ76 **pp_Var7;
  uint uVar8;
  int iVar9;
  float fVar10;
  char local_38 [4];
  int local_34;
  int local_30;
  ParameterDB local_2c;
  char local_28 [16];
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  ParameterDB::ParameterDB(&local_2c,"chunk.odf");
  ParameterDB::Get(&local_2c,0xf7d2616f,0x88f1ef89,local_28,0x10,"bsmoke.0");
  iVar4 = GetSpriteIndex(local_28);
  this->smokeTexture = iVar4;
  ParameterDB::Get(&local_2c,0xf7d2616f,0xdd33060c,&this->smokeFrames,0x10);
  ParameterDB::Get(&local_2c,0xf7d2616f,0x567840fc,&this->smokeLifespan,1.6);
  ParameterDB::Get(&local_2c,0xf7d2616f,0x1f6a810,&this->smokePause,0.1);
  ParameterDB::Get(&local_2c,0xf7d2616f,0x8566cba4,&this->smokeRadius,0.8);
  ParameterDB::Get(&local_2c,0xf7d2616f,0xbb8ad7d1,&this->smokeVariance,1.5);
  ParameterDB::Get(&local_2c,0xf7d2616f,0x40a86add,&this->smokeInherit,0.5);
  this->chunkCount = 0;
  p_Var5 = create_obj((_OBJ76 *)0x0,".\\fun3d\\ChunkEffect.cpp");
  *(undefined4 *)&p_Var5->id = 0x6e756863;
  *(undefined4 *)((int)&p_Var5->id + 4) = 0x6b;
  p_Var5->flags = 0x101;
  p_Var5->class_id = CLASS_ID_CHUNK;
  p_Var5->class_ptr = (void *)0x0;
  p_Var5->sibling = (_OBJ76 *)0x0;
  p_Var5->child = (_OBJ76 *)0x0;
  ptVar6 = add_entity(p_Var5,0,(CLSN_BOXES *)0x0,(float *)0x0);
  this->ent = ptVar6;
  ParameterDB::Get(&local_2c,0xf7d2616f,0x26c0023a,&this->chunkletCount,2);
  lVar3 = (ulonglong)(uint)this->chunkletCount * 4;
  pp_Var7 = operator_new__(-(uint)((int)((ulonglong)lVar3 >> 0x20) != 0) | (uint)lVar3);
  this->chunkletList = pp_Var7;
  if (0 < this->chunkletCount) {
    local_34 = 0;
    local_30 = 1;
    do {
      iVar4 = local_34;
      sprintf(local_38,"%d",local_30);
      sprintf(local_18,"chunk%d.geo",local_30);
      uVar8 = Hash(local_38,0x3acf08fb);
      ParameterDB::Get(&local_2c,0xf7d2616f,uVar8,local_18,0x10,local_18);
      p_Var5 = create_obj((_OBJ76 *)0x0,".\\fun3d\\ChunkEffect.cpp");
      *(_OBJ76 **)(iVar4 + (int)this->chunkletList) = p_Var5;
      iVar9 = GeoCache_AddRep(*(_OBJ76 **)((int)this->chunkletList + iVar4),local_18,0,0);
      if (iVar9 == 0) {
        TraceWarning("ChunkEffect \"%s\" could not add geometry \"%s\"\n");
      }
      p_Var5 = *(_OBJ76 **)(iVar4 + (int)this->chunkletList);
      get_obj_bounding_box(p_Var5,&(p_Var5->bBox).min,&(p_Var5->bBox).max);
      iVar9 = *(int *)(iVar4 + (int)this->chunkletList);
      *(float *)(iVar9 + 200) = (*(float *)(iVar9 + 0xe4) + *(float *)(iVar9 + 0xd8)) * 0.5;
      iVar9 = *(int *)(iVar4 + (int)this->chunkletList);
      *(float *)(iVar9 + 0xcc) = (*(float *)(iVar9 + 0xe8) + *(float *)(iVar9 + 0xdc)) * 0.5;
      iVar9 = *(int *)(iVar4 + (int)this->chunkletList);
      *(float *)(iVar9 + 0xd0) = (*(float *)(iVar9 + 0xec) + *(float *)(iVar9 + 0xe0)) * 0.5;
      p_Var5 = *(_OBJ76 **)(iVar4 + (int)this->chunkletList);
      fVar10 = get_obj_radius(p_Var5,(p_Var5->bSphere).origin);
      piVar1 = (int *)((int)this->chunkletList + local_34);
      local_34 = local_34 + 4;
      *(float *)(*piVar1 + 0xd4) = fVar10;
      iVar4 = local_30 + 1;
      bVar2 = local_30 < this->chunkletCount;
      local_30 = iVar4;
    } while (bVar2);
  }
  ParameterDB::~ParameterDB(&local_2c);
  return;
}
