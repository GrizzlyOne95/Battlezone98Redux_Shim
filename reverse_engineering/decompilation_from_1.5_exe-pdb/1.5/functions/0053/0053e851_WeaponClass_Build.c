/*
 * Entry: 0053e851
 * Name: WeaponClass::Build
 * Namespace: WeaponClass
 * Signature: Weapon * Build(WeaponClass * this, _OBJ76 * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Weapon * __thiscall WeaponClass::Build(WeaponClass *this,_OBJ76 *param_1,_OBJ76 *param_2)

{
  _OBJ76 *p_Var1;
  Weapon *pWVar2;
  
  p_Var1 = create_obj(param_2,".\\fun3d\\WeaponClass.cpp");
  *(int *)&p_Var1->id = (int)this->cfg;
  *(undefined4 *)((int)&p_Var1->id + 4) = *(undefined4 *)((int)&this->cfg + 4);
  p_Var1->flags = param_1->flags & 0xf0010;
  p_Var1->class_id = CLASS_ID_WEAPON;
  pWVar2 = (Weapon *)(**(code **)(this->_padding_ + 8))(p_Var1);
  p_Var1->class_ptr = pWVar2;
  return pWVar2;
}
