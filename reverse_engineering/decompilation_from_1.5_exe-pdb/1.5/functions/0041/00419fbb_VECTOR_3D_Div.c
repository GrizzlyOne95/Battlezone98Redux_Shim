/*
 * Entry: 00419fbb
 * Name: VECTOR_3D_Div
 * Namespace: Global
 * Signature: int VECTOR_3D_Div(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl VECTOR_3D_Div(lua_State *param_1)

{
  int iVar1;
  VECTOR_3D *pVVar2;
  VECTOR_3D *pVVar3;
  int iVar4;
  lua_State *unaff_EDI;
  double dVar5;
  float local_14;
  float local_10;
  float local_c;
  
  iVar4 = 1;
  iVar1 = lua_isnumber(param_1,1);
  if (iVar1 == 0) {
    iVar1 = lua_isnumber(param_1,2);
    if (iVar1 == 0) {
      pVVar2 = RequireVector(param_1,1);
      pVVar3 = RequireVector(param_1,2);
      local_14 = pVVar2->x / pVVar3->x;
      local_10 = pVVar2->y / pVVar3->y;
      local_c = pVVar2->z / pVVar3->z;
      pVVar2 = NewVector(unaff_EDI);
      iVar4 = 0;
      goto LAB_0041a07c;
    }
    pVVar2 = RequireVector(param_1,1);
    dVar5 = lua_tonumber(param_1,2);
    local_c = 1.0 / (float)dVar5;
    local_14 = pVVar2->x * local_c;
    local_10 = pVVar2->y * local_c;
    local_c = local_c * pVVar2->z;
  }
  else {
    dVar5 = lua_tonumber(param_1,1);
    local_c = (float)dVar5;
    pVVar2 = RequireVector(param_1,2);
    local_14 = local_c / pVVar2->x;
    local_10 = local_c / pVVar2->y;
    local_c = local_c / pVVar2->z;
  }
  pVVar2 = NewVector(unaff_EDI);
LAB_0041a07c:
  pVVar2->x = local_14;
  pVVar2->y = local_10;
  pVVar2->z = local_c;
  return iVar4;
}
