/*
 * Entry: 00419d1e
 * Name: VECTOR_3D_Index
 * Namespace: Global
 * Signature: int VECTOR_3D_Index(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl VECTOR_3D_Index(lua_State *param_1)

{
  float fVar1;
  VECTOR_3D *pVVar2;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  undefined4 unaff_EDI;
  
  pVVar2 = GetVector(param_1,1);
  if (pVVar2 == (VECTOR_3D *)0x0) {
LAB_00419d34:
    iVar3 = 0;
  }
  else {
    pcVar4 = luaL_checklstring(param_1,2,(uint *)0x0);
    uVar5 = Hash(pcVar4,0x811c9dc5);
    if (uVar5 == 0xfc0c4ef4) {
      fVar1 = pVVar2->y;
    }
    else if (uVar5 == 0xfd0c5087) {
      fVar1 = pVVar2->x;
    }
    else {
      if (uVar5 != 0xff0c53ad) goto LAB_00419d34;
      fVar1 = pVVar2->z;
    }
    lua_pushnumber(param_1,(double)CONCAT44(unaff_EDI,(int)((ulonglong)(double)fVar1 >> 0x20)));
    iVar3 = 1;
  }
  return iVar3;
}
