/*
 * Entry: 004b3377
 * Name: Tug::SetCargo
 * Namespace: Tug
 * Signature: void SetCargo(Tug * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Tug::SetCargo(Tug *this,GameObject *param_1)

{
  _OBJ76 *p_Var1;
  VECTOR_3D local_10;
  
  if (this->cargo != (GameObject *)0x0) {
    this->cargo->isCargo = false;
    this->cargo->tug = (GameObject *)0x0;
    this->hitchCargo = (_OBJ76 *)0x0;
    p_Var1 = this->cargo->obj;
    local_10.x = (float)(p_Var1->transform).posit_x;
    local_10.y = (float)(p_Var1->transform).posit_y;
    local_10.z = (float)(p_Var1->transform).posit_z;
    Terrain_GetHeightAndNormal((double)local_10.x,(double)local_10.z,&local_10.y,(VECTOR_3D *)0x0);
    GameObject::SetOrigin(this->cargo,&local_10);
  }
  if (param_1 != (GameObject *)0x0) {
    param_1->isCargo = true;
    param_1->tug = (GameObject *)this;
    p_Var1 = (_OBJ76 *)(**(code **)(param_1->_padding_ + 0x28))();
    this->hitchCargo = p_Var1;
  }
  this->cargo = param_1;
  return;
}
