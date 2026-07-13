/*
 * Entry: 004d3cb6
 * Name: ParticleEffect::Submit
 * Namespace: ParticleEffect
 * Signature: void Submit(ParticleEffect * this, CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ParticleEffect::Submit(ParticleEffect *this,CAMERA *param_1)

{
  int iVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  _ZSORTING *p_Var5;
  uint uVar6;
  long lVar7;
  VECTOR_3D local_18;
  Particle *local_c;
  uint local_8;
  
  local_8 = this->indexFirst;
  if (local_8 != this->indexLast) {
    do {
      uVar6 = local_8 + 1;
      local_c = this->particleList + local_8;
      local_8 = uVar6;
      if (0xff < uVar6) {
        local_8 = 0;
      }
      local_18.x = (local_c->pos).x;
      local_18.y = (local_c->pos).y;
      local_18.z = (local_c->pos).z;
      Vector_Transform(&local_18,&local_18,1,&param_1->Matrix);
      lVar7 = Camera_Bounding_Sphere_Test(param_1,&local_18,this->particleRadius);
      p_Var5 = SortingTableCurrent;
      if (lVar7 < 1) {
        SortingTableCurrent->vcnt = 0;
        p_Var5->Type = 9;
        iVar1 = this->particleTexture;
        iVar2 = local_c->frame;
        p_Var5->Bitmap_Operation = 0x50004;
        (p_Var5->Skin_Color).Texture = (TEXTURE *)(iVar1 + iVar2);
        fVar3 = 1.0 / local_18.z;
        p_Var5[1].vcnt = (long)(param_1->Const_x * local_18.x * fVar3 + param_1->Orig_x);
        p_Var5[1].Skin_Color =
             (POLYGON_SKIN)(param_1->Const_y * local_18.y * fVar3 + param_1->Orig_y);
        p_Var5[1].Bitmap_Operation = (long)local_18.z;
        fVar4 = this->particleRadius * param_1->Const_x * fVar3;
        p_Var5[1].Type = (long)(fVar4 + fVar4);
        p_Var5[1].Z_Value = param_1->Const_y * this->particleRadius * fVar3 * -2.0;
        p_Var5[1].Previous = (_ZSORTING *)local_18.x;
        p_Var5[2].vcnt = (long)local_18.y;
        p_Var5[2].Skin_Color = (POLYGON_SKIN)local_18.z;
        p_Var5[1].Next = (_ZSORTING *)this->particleRadius;
        fVar3 = local_18.z - this->particleRadius;
        p_Var5->Z_Value = fVar3;
        ZSORTAdd(fVar3);
      }
    } while (local_8 != this->indexLast);
  }
  return;
}
