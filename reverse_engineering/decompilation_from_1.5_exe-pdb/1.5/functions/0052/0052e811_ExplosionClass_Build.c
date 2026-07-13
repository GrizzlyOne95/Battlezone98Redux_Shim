/*
 * Entry: 0052e811
 * Name: ExplosionClass::Build
 * Namespace: ExplosionClass
 * Signature: Explosion * Build(ExplosionClass * this, MAT_3D * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Explosion * __thiscall ExplosionClass::Build(ExplosionClass *this,MAT_3D *param_1,_OBJ76 *param_2)

{
  _OBJ76 *p_Var1;
  Explosion *pEVar2;
  
  p_Var1 = this->freeObj->child;
  if (p_Var1 == (_OBJ76 *)0x0) {
    p_Var1 = create_obj((_OBJ76 *)0x0,".\\fun3d\\ExplosionClass.cpp");
    *(int *)&p_Var1->id = (int)this->cfg;
    *(undefined4 *)((int)&p_Var1->id + 4) = *(undefined4 *)((int)&this->cfg + 4);
    p_Var1->class_id = CLASS_ID_EXPLOSION;
    pEVar2 = (Explosion *)(**(code **)(this->_padding_ + 8))(p_Var1);
    p_Var1->class_ptr = pEVar2;
  }
  else {
    remove_obj_from_tree(p_Var1);
    pEVar2 = p_Var1->class_ptr;
  }
  (**(code **)(pEVar2->_padding_ + 4))(param_1,param_2);
  return pEVar2;
}
