/*
 * Entry: 0041746f
 * Name: BuildDirectionalMatrix
 * Namespace: Global
 * Signature: int BuildDirectionalMatrix(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Type propagation algorithm not settling */

int __cdecl BuildDirectionalMatrix(lua_State *param_1)

{
  MAT_3D *pMVar1;
  int iVar2;
  VECTOR_3D *unaff_ESI;
  lua_TValue *plVar3;
  VECTOR_3D *unaff_EDI;
  lua_State *__return_storage_ptr__;
  lua_State local_84;
  
  GetVector(param_1,1);
  GetVector(param_1,2);
  __return_storage_ptr__ = &local_84;
  pMVar1 = Build_Directinal_Matrix((MAT_3D *)__return_storage_ptr__,unaff_EDI,unaff_ESI);
  plVar3 = (lua_TValue *)&local_84.hookcount;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(_func___cdecl_void_lua_State_ptr_lua_Debug_ptr **)&plVar3->value =
         (_func___cdecl_void_lua_State_ptr_lua_Debug_ptr *)pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    plVar3 = (lua_TValue *)((int)&plVar3->value + 4);
  }
  pMVar1 = NewMatrix(__return_storage_ptr__);
  plVar3 = (lua_TValue *)&local_84.hookcount;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    pMVar1->right_x = (float)*(_func___cdecl_void_lua_State_ptr_lua_Debug_ptr **)&plVar3->value;
    plVar3 = (lua_TValue *)((int)&plVar3->value + 4);
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
  }
  return 1;
}
