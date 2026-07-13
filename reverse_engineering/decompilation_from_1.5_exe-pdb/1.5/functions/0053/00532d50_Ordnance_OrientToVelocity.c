/*
 * Entry: 00532d50
 * Name: Ordnance::OrientToVelocity
 * Namespace: Ordnance
 * Signature: void OrientToVelocity(Ordnance * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Ordnance::OrientToVelocity(Ordnance *this)

{
  _OBJ76 *p_Var1;
  VECTOR_3D *pVVar2;
  MAT_3D *pMVar3;
  VECTOR_3D local_24;
  float local_18;
  float fStack_14;
  float fStack_10;
  float *local_c;
  VECTOR_3D *local_8;
  
  if (0.0001 <= (this->euler).v_mag) {
    p_Var1 = this->obj;
    pMVar3 = &p_Var1->transform;
    pVVar2 = Normalize_Vector(&local_24,&(this->euler).v);
    local_18 = pVVar2->x;
    fStack_14 = pVVar2->y;
    fStack_10 = pVVar2->z;
    local_8 = (VECTOR_3D *)&(p_Var1->transform).front_x;
    *(float *)local_8 = local_18;
    local_c = &(p_Var1->transform).up_x;
    (p_Var1->transform).front_y = fStack_14;
    (p_Var1->transform).front_z = fStack_10;
    pVVar2 = Cross_Product(&local_24,(VECTOR_3D *)local_c,local_8);
    pMVar3->right_x = pVVar2->x;
    (p_Var1->transform).right_y = pVVar2->y;
    (p_Var1->transform).right_z = pVVar2->z;
    pVVar2 = Normalize_Vector(&local_24,(VECTOR_3D *)pMVar3);
    pMVar3->right_x = pVVar2->x;
    (p_Var1->transform).right_y = pVVar2->y;
    (p_Var1->transform).right_z = pVVar2->z;
    pVVar2 = Cross_Product(&local_24,local_8,(VECTOR_3D *)pMVar3);
    *local_c = pVVar2->x;
    local_c[1] = pVVar2->y;
    local_c[2] = pVVar2->z;
  }
  return;
}
