/*
 * Entry: 004d1188
 * Name: LightningFeature::RenderBoltSegs
 * Namespace: LightningFeature
 * Signature: void RenderBoltSegs(LightningFeature * this, BoltEmitter * param_1, CAMERA * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
LightningFeature::RenderBoltSegs(LightningFeature *this,BoltEmitter *param_1,CAMERA *param_2)

{
  _ZSORTING *p_Var1;
  _ZSORTING **pp_Var2;
  float *pfVar3;
  VECTOR_3D VVar4;
  _ZSORTING *p_Var5;
  VECTOR_3D *pVVar6;
  long lVar7;
  float fVar8;
  VECTOR_3D local_58;
  VECTOR_3D local_4c;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  VECTOR_3D *local_1c;
  VECTOR_3D *local_18;
  int local_14;
  float local_10;
  float local_c;
  uchar *local_8;
  
  Vector_Transform(Vertex_Pool,param_1->vertex,param_1->vertices,&param_2->Matrix);
  local_14 = 0;
  local_8 = &param_1->segment[0].width;
  local_10 = (float)*local_8 * 0.005;
  if (0 < param_1->segments) {
    do {
      local_18 = Vertex_Pool + local_8[-1];
      local_28 = local_18->x;
      local_24 = local_18->y;
      local_20 = local_18->z;
      local_1c = Vertex_Pool + ((BoltSeg *)(local_8 + -2))->start;
      local_34 = local_1c->x;
      local_30 = local_1c->y;
      local_2c = local_1c->z;
      local_40 = local_28 + local_34;
      local_3c = local_24 + local_30;
      local_38 = local_20 + local_2c;
      VVar4.y = local_3c;
      VVar4.x = local_40;
      VVar4.z = local_38;
      pVVar6 = ScaleVector(&local_58,0.5,VVar4);
      local_4c.x = pVVar6->x;
      local_c = (float)*local_8 * 0.005;
      local_4c.y = pVVar6->y;
      local_4c.z = pVVar6->z;
      lVar7 = Camera_Bounding_Sphere_Test(param_2,&local_4c,10.0);
      p_Var5 = SortingTableCurrent;
      if (lVar7 < 1) {
        SortingTableCurrent->Bitmap_Operation = 0;
        p_Var5->Type = 8;
        p_Var5->vcnt = 4;
        (p_Var5->Skin_Color).Color = BoltSet.color;
        p_Var1 = p_Var5 + 1;
        ((VECTOR_3D *)&p_Var1->vcnt)->x = local_1c->x;
        p_Var5[1].Skin_Color = (POLYGON_SKIN)local_1c->y;
        p_Var5[1].Bitmap_Operation = (long)local_1c->z;
        pp_Var2 = &p_Var5[1].Previous;
        ((VECTOR_3D *)&p_Var1->vcnt)->x = ((VECTOR_3D *)&p_Var1->vcnt)->x + local_10;
        p_Var5[1].Next = (_ZSORTING *)TerrainIntensity;
        *pp_Var2 = (_ZSORTING *)local_18->x;
        p_Var5[2].vcnt = (long)local_18->y;
        p_Var5[2].Skin_Color = (POLYGON_SKIN)local_18->z;
        *pp_Var2 = (_ZSORTING *)((float)*pp_Var2 + local_c);
        pp_Var2 = &p_Var5[2].Next;
        p_Var5[2].Z_Value = TerrainIntensity;
        *pp_Var2 = (_ZSORTING *)local_18->x;
        p_Var5[2].Previous = (_ZSORTING *)local_18->y;
        p_Var5[3].vcnt = (long)local_18->z;
        *pp_Var2 = (_ZSORTING *)((float)*pp_Var2 - local_c);
        pfVar3 = &p_Var5[3].Z_Value;
        p_Var5[3].Type = (long)TerrainIntensity;
        *pfVar3 = local_1c->x;
        p_Var5[3].Next = (_ZSORTING *)local_1c->y;
        p_Var5[3].Previous = (_ZSORTING *)local_1c->z;
        *pfVar3 = *pfVar3 - local_10;
        p_Var5[4].Bitmap_Operation = (long)TerrainIntensity;
        fVar8 = GetMin((POINT_3D *)p_Var1,4);
        p_Var5->Z_Value = fVar8;
        ZSORTAdd(fVar8);
      }
      local_14 = local_14 + 1;
      local_10 = local_c;
      local_8 = local_8 + 4;
    } while (local_14 < param_1->segments);
  }
  return;
}
