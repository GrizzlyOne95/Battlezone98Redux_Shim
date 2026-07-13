/*
 * Entry: 00460ae4
 * Name: BuildObject
 * Namespace: Global
 * Signature: int BuildObject(char * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl BuildObject(char *param_1,int param_2,int param_3)

{
  int *piVar1;
  _OBJ76 *p_Var2;
  VECTOR_3D VVar3;
  VECTOR_3D VVar4;
  float *pfVar5;
  int iVar6;
  VECTOR_3D *pVVar7;
  VECTOR_3D local_20;
  VECTOR_3D local_14;
  GameObject *local_8;
  
  local_8 = GameObjectHandle::GetObj(param_3);
  iVar6 = 0;
  if (local_8 != (GameObject *)0x0) {
    piVar1 = &local_8->_padding_;
    pfVar5 = (float *)(**(code **)(*piVar1 + 0xc))();
    local_14.x = *pfVar5;
    local_14.y = pfVar5[1];
    local_14.z = pfVar5[2];
    iVar6 = (**(code **)*piVar1)();
    iVar6 = *(int *)(iVar6 + 0x28);
    if ((0 < iVar6) && ((iVar6 < 3 || (iVar6 == 6)))) {
      p_Var2 = local_8->obj;
      VVar4.x = (p_Var2->transform).front_x;
      VVar4.y = (p_Var2->transform).front_y;
      VVar4.z = (p_Var2->transform).front_z;
      VVar3.y = local_14.y;
      VVar3.x = local_14.x;
      VVar3.z = local_14.z;
      pVVar7 = AddMultVectors(&local_20,VVar3,local_8->collisionRadius,VVar4);
      local_14.x = pVVar7->x;
      local_14.y = pVVar7->y;
      local_14.z = pVVar7->z;
    }
    iVar6 = BuildObject(param_1,param_2,&local_14);
  }
  return iVar6;
}
