/*
 * Entry: 00534df9
 * Name: OrdnanceClass::Build
 * Namespace: OrdnanceClass
 * Signature: Ordnance * Build(OrdnanceClass * this, MAT_3D * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Ordnance * __thiscall OrdnanceClass::Build(OrdnanceClass *this,MAT_3D *param_1,_OBJ76 *param_2)

{
  _OBJ76 *p_Var1;
  _OBJ76 *p_Var2;
  int iVar3;
  Ordnance *pOVar4;
  BBOX *pBVar5;
  BBOX *pBVar6;
  
  p_Var2 = this->freeOrd->child;
  if (p_Var2 == (_OBJ76 *)0x0) {
    p_Var2 = create_obj((_OBJ76 *)0x0,".\\fun3d\\OrdnanceClass.cpp");
    *(int *)&p_Var2->id = (int)this->cfg;
    *(undefined4 *)((int)&p_Var2->id + 4) = *(undefined4 *)((int)&this->cfg + 4);
    p_Var2->geom = (_GEOMETRY *)0x0;
    if (this->ord->geom != (_GEOMETRY *)0x0) {
      GeoCache_Clone(this->ord,p_Var2);
      pBVar5 = &this->ord->bBox;
      pBVar6 = &p_Var2->bBox;
      for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
        (pBVar6->min).x = (pBVar5->min).x;
        pBVar5 = (BBOX *)&(pBVar5->min).y;
        pBVar6 = (BBOX *)&(pBVar6->min).y;
      }
      p_Var1 = this->ord;
      (p_Var2->bSphere).origin.x = (p_Var1->bSphere).origin.x;
      (p_Var2->bSphere).origin.y = (p_Var1->bSphere).origin.y;
      (p_Var2->bSphere).origin.z = (p_Var1->bSphere).origin.z;
      (p_Var2->bSphere).radius = (p_Var1->bSphere).radius;
    }
    p_Var2->class_id = CLASS_ID_ORDNANCE;
    pOVar4 = (Ordnance *)(**(code **)(this->_padding_ + 8))(p_Var2);
    p_Var2->class_ptr = pOVar4;
  }
  else {
    remove_obj_from_tree(p_Var2);
    if (p_Var2 == (_OBJ76 *)0x0) {
      pOVar4 = (Ordnance *)0x0;
    }
    else {
      pOVar4 = p_Var2->class_ptr;
    }
  }
  (**(code **)(pOVar4->_padding_ + 4))(param_1,param_2);
  return pOVar4;
}
