/*
 * Entry: 004b3066
 * Name: Tug::RegCollision
 * Namespace: Tug
 * Signature: bool RegCollision(Tug * this, _OBJ76 * param_1, CLSN_INFO * param_2, CLSN_INFO * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Tug::RegCollision(Tug *this,_OBJ76 *param_1,CLSN_INFO *param_2,CLSN_INFO *param_3)

{
  bool bVar1;
  _OBJ76 *p_Var2;
  _OBJ76 *p_Var3;
  
  if (this->cargo != (GameObject *)0x0) {
    p_Var2 = (_OBJ76 *)(**(code **)(this->cargo->_padding_ + 0x30))();
    p_Var3 = obj_get_root(param_1);
    if (p_Var3 == p_Var2) {
      return false;
    }
  }
  bVar1 = Craft::RegCollision((Craft *)this,param_1,param_2,param_3);
  return bVar1;
}
