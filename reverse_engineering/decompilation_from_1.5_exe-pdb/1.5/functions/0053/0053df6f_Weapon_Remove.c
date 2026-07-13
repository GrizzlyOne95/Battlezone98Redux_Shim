/*
 * Entry: 0053df6f
 * Name: Weapon::Remove
 * Namespace: Weapon
 * Signature: void Remove(Weapon * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Weapon::Remove(Weapon *this)

{
  _OBJ76 *p_Var1;
  
  p_Var1 = this->obj;
  ClassDelete(p_Var1);
  remove_obj(p_Var1,".\\fun3d\\Weapon.cpp");
  return;
}
