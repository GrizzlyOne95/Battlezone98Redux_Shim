/*
 * Entry: 00482d21
 * Name: Building::Init
 * Namespace: Building
 * Signature: Building * Init(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Building * __cdecl Building::Init(_OBJ76 *param_1)

{
  int *piVar1;
  BuildingClass *pBVar2;
  Building *pBVar3;
  _OBJ76 *p_Var4;
  
  pBVar2 = (BuildingClass *)GameObjectClass::Find(param_1->id);
  if (pBVar2 == (BuildingClass *)0x0) {
    Trace("Building::Init - bad building class (%.8s)\n");
    pBVar2 = &buildingClass;
  }
  pBVar3 = (Building *)(**(code **)(pBVar2->_padding_ + 4))(param_1);
  piVar1 = param_1->class_ptr;
  *piVar1 = (int)pBVar3;
  piVar1[1] = (int)param_1;
  p_Var4 = obj_get_root(param_1);
  pBVar3->root = p_Var4;
  (**(code **)(pBVar3->_padding_ + 4))(*(ushort *)((int)&param_1->flags + 2) & 0xf);
  return pBVar3;
}
