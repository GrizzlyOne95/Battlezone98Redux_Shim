/*
 * Entry: 00419e9d
 * Name: VECTOR_3D_Sub
 * Namespace: Global
 * Signature: int VECTOR_3D_Sub(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl VECTOR_3D_Sub(lua_State *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  VECTOR_3D *pVVar7;
  VECTOR_3D *pVVar8;
  lua_State *unaff_EDI;
  
  pVVar7 = RequireVector(param_1,1);
  pVVar8 = RequireVector(param_1,2);
  fVar1 = pVVar8->x;
  fVar2 = pVVar8->y;
  fVar3 = pVVar8->z;
  fVar4 = pVVar7->x;
  fVar5 = pVVar7->y;
  fVar6 = pVVar7->z;
  pVVar7 = NewVector(unaff_EDI);
  pVVar7->x = fVar4 - fVar1;
  pVVar7->y = fVar5 - fVar2;
  pVVar7->z = fVar6 - fVar3;
  return 1;
}
