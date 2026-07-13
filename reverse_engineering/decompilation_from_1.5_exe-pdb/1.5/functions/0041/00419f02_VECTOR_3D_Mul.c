/*
 * Entry: 00419f02
 * Name: VECTOR_3D_Mul
 * Namespace: Global
 * Signature: int VECTOR_3D_Mul(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl VECTOR_3D_Mul(lua_State *param_1)

{
  float fVar1;
  int iVar2;
  VECTOR_3D *pVVar3;
  VECTOR_3D *pVVar4;
  lua_State *unaff_EDI;
  double dVar5;
  VECTOR_3D local_20;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  iVar2 = lua_isnumber(param_1,1);
  if (iVar2 == 0) {
    iVar2 = lua_isnumber(param_1,2);
    if (iVar2 == 0) {
      pVVar3 = RequireVector(param_1,1);
      pVVar4 = RequireVector(param_1,2);
      local_14 = pVVar4->x * pVVar3->x;
      local_10 = pVVar4->y * pVVar3->y;
      local_c = pVVar4->z * pVVar3->z;
      goto LAB_00419fa4;
    }
    pVVar3 = RequireVector(param_1,1);
    dVar5 = lua_tonumber(param_1,2);
    fVar1 = (float)dVar5;
  }
  else {
    dVar5 = lua_tonumber(param_1,1);
    local_8 = (float)dVar5;
    pVVar3 = RequireVector(param_1,2);
    fVar1 = local_8;
  }
  pVVar3 = ScaleVector(&local_20,fVar1,*pVVar3);
  local_14 = pVVar3->x;
  local_10 = pVVar3->y;
  local_c = pVVar3->z;
LAB_00419fa4:
  pVVar3 = NewVector(unaff_EDI);
  pVVar3->x = local_14;
  pVVar3->y = local_10;
  pVVar3->z = local_c;
  return 1;
}
