/*
 * Entry: 0041730f
 * Name: BuildPositionRotationMatrix
 * Namespace: Global
 * Signature: int BuildPositionRotationMatrix(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl BuildPositionRotationMatrix(lua_State *param_1)

{
  float fVar1;
  VECTOR_3D *pVVar2;
  MAT_3D *pMVar3;
  int iVar4;
  float *pfVar5;
  lua_State *unaff_EDI;
  double dVar6;
  MAT_3D local_98;
  float local_58 [16];
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  dVar6 = luaL_optnumber(param_1,1,0.0);
  local_14 = (float)dVar6;
  dVar6 = luaL_optnumber(param_1,2,0.0);
  local_10 = (float)dVar6;
  dVar6 = luaL_optnumber(param_1,3,0.0);
  local_18 = (float)dVar6;
  pVVar2 = GetVector(param_1,4);
  if (pVVar2 == (VECTOR_3D *)0x0) {
    dVar6 = luaL_optnumber(param_1,4,0.0);
    local_c = (float)dVar6;
    dVar6 = luaL_optnumber(param_1,5,0.0);
    local_8 = (float)dVar6;
    dVar6 = luaL_optnumber(param_1,6,0.0);
    fVar1 = (float)dVar6;
  }
  else {
    local_c = pVVar2->x;
    local_8 = pVVar2->y;
    fVar1 = pVVar2->z;
  }
  pMVar3 = Build_Position_Rotation_Matrix
                     (&local_98,local_14,local_10,local_18,local_c,local_8,fVar1);
  pfVar5 = local_58;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *pfVar5 = pMVar3->right_x;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
    pfVar5 = pfVar5 + 1;
  }
  pMVar3 = NewMatrix(unaff_EDI);
  pfVar5 = local_58;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar3->right_x = *pfVar5;
    pfVar5 = pfVar5 + 1;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
  }
  return 1;
}
