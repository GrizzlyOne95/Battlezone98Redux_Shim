/*
 * Entry: 0052dcab
 * Name: Explosion::Simulate
 * Namespace: Explosion
 * Signature: void Simulate(Explosion * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Explosion::Simulate(Explosion *this,float param_1)

{
  ulong *puVar1;
  VECTOR_3D *pVVar2;
  bool bVar3;
  GameObject *pGVar4;
  _OBJ76 *p_Var5;
  int iVar6;
  float *pfVar7;
  int unaff_EDI;
  float fVar8;
  Range_Search_Results local_70;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  VECTOR_3D local_2c;
  int local_20;
  float local_1c;
  int *local_18;
  float local_14;
  Explosion *local_10;
  float local_c;
  float local_8;
  
  fVar8 = this->explosionClass->frameRate * param_1 + this->frameIndex;
  this->frameIndex = fVar8;
  if (this->frameLimit <= fVar8) {
    puVar1 = &this->obj->flags;
    *puVar1 = *puVar1 | 0x200;
  }
  if (0.0 < this->omegaShake) {
    local_10 = this;
    local_20 = Set_Rounding(unaff_EDI);
    local_1c = this->explosionClass->damageRadius;
    local_1c = local_1c * local_1c;
    local_14 = this->explosionClass->explRadius;
    p_Var5 = this->obj;
    local_2c.x = (p_Var5->bSphere).origin.x;
    local_14 = local_14 * local_14;
    local_2c.y = (p_Var5->bSphere).origin.y;
    local_2c.z = (p_Var5->bSphere).origin.z;
    Vector_Transform(&local_2c,&local_2c,1,&p_Var5->transform);
    Range::Search(GameObject::objectRange,(double)local_2c.x,(double)local_2c.z,
                  (double)this->explosionClass->damageRadius,&local_70);
    bVar3 = Range_Search_Results::Get_Next_Object(&local_70,&local_18);
    if (bVar3) {
      do {
        pGVar4 = GameObject::GetObj(*local_18);
        if (pGVar4 != (GameObject *)0x0) {
          p_Var5 = (_OBJ76 *)(**(code **)(pGVar4->_padding_ + 0x30))();
          iVar6 = dynamic_object(p_Var5);
          if (iVar6 != 0) {
            local_44 = local_2c.x;
            local_40 = local_2c.y;
            local_3c = local_2c.z;
            pfVar7 = (float *)(**(code **)(pGVar4->_padding_ + 0xc))();
            local_38 = *pfVar7;
            local_34 = pfVar7[1];
            local_30 = pfVar7[2];
            fVar8 = (local_34 - local_40) * (local_34 - local_40) +
                    (local_30 - local_3c) * (local_30 - local_3c) +
                    (local_38 - local_44) * (local_38 - local_44);
            if (fVar8 < local_1c) {
              if (local_14 <= fVar8) {
                local_8 = ((local_1c - fVar8) * local_10->omegaShake * param_1) /
                          (local_1c - local_14);
              }
              else {
                local_8 = local_10->omegaShake * param_1;
              }
              local_c = Get_Time();
              local_c = local_c + local_c;
              fVar8 = Noise1D(local_c + 8.53);
              (pGVar4->euler).omega.x = fVar8 * local_8 + fVar8 * local_8 + (pGVar4->euler).omega.x;
              fVar8 = Noise1D(local_c + 17.67);
              (pGVar4->euler).omega.y = fVar8 * local_8 + (pGVar4->euler).omega.y;
              fVar8 = Noise1D(local_c + 5.19);
              pVVar2 = &(pGVar4->euler).v;
              (pGVar4->euler).omega.z = fVar8 * local_8 + fVar8 * local_8 + (pGVar4->euler).omega.z;
              fVar8 = Noise1D(local_c);
              pVVar2->x = fVar8 * local_8 * 5.0 + pVVar2->x;
              fVar8 = Noise1D(local_c + 2.27);
              (pGVar4->euler).v.y = fVar8 * local_8 + fVar8 * local_8 + (pGVar4->euler).v.y;
              fVar8 = Noise1D(local_c + 23.41);
              (pGVar4->euler).v.z = fVar8 * local_8 * 5.0 + (pGVar4->euler).v.z;
              fVar8 = VecLen(*pVVar2);
              (pGVar4->euler).v_mag = fVar8;
              if (fVar8 <= 0.0) {
                fVar8 = 1e+30;
              }
              else {
                fVar8 = 1.0 / fVar8;
              }
              (pGVar4->euler).v_mag_inv = fVar8;
            }
          }
        }
        bVar3 = Range_Search_Results::Get_Next_Object(&local_70,&local_18);
        this = local_10;
      } while (bVar3);
    }
    this->omegaShake = this->omegaShake - this->deltaShake * param_1;
    Set_Rounding(unaff_EDI);
  }
  return;
}
