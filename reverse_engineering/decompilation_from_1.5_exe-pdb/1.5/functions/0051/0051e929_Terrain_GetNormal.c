/*
 * Entry: 0051e929
 * Name: Terrain_GetNormal
 * Namespace: Global
 * Signature: VECTOR_3D * Terrain_GetNormal(VECTOR_3D * __return_storage_ptr__, double param_1, double param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl
Terrain_GetNormal(VECTOR_3D *__return_storage_ptr__,double param_1,double param_2)

{
  double dVar1;
  float fVar2;
  float fVar3;
  long lVar4;
  long lVar5;
  VECTOR_3D *pVVar6;
  long unaff_ESI;
  int unaff_EDI;
  float10 extraout_ST0;
  float10 fVar7;
  float10 fVar8;
  float10 extraout_ST0_00;
  undefined4 in_stack_00000008;
  VECTOR_3D local_2c;
  VECTOR_3D local_20;
  int local_14;
  float local_10;
  float local_c;
  int local_8;
  
  dVar1 = (double)((float)(double)CONCAT44(param_1._0_4_,in_stack_00000008) * Terrain.Grid_Scale);
  in_stack_00000008 = SUB84(dVar1,0);
  param_1._0_4_ = (undefined4)((ulonglong)dVar1 >> 0x20);
  dVar1 = (double)(Terrain.Grid_Scale * (float)(double)CONCAT44(param_2._0_4_,param_1._4_4_));
  Set_Rounding(unaff_EDI);
  local_20.y = (float)(longlong)ROUND((double)CONCAT44(param_1._0_4_,in_stack_00000008));
  fVar2 = local_20.y;
  local_c = local_20.y;
  local_20._4_8_ = (BADTYPE)ROUND(dVar1);
  fVar3 = local_20.y;
  local_10 = local_20.y;
  Set_Rounding(unaff_EDI);
  lVar4 = Terrain_Get_Height(unaff_EDI,unaff_ESI);
  local_14 = (int)fVar3 + 1;
  local_20.z = (float)((int)fVar2 + 1);
  local_8 = Terrain_Get_Height(unaff_EDI,unaff_ESI);
  if (dVar1 - (double)(int)local_10 <=
      (double)CONCAT44(param_1._0_4_,in_stack_00000008) - (double)(int)local_c) {
    lVar5 = Terrain_Get_Height(unaff_EDI,unaff_ESI);
    fVar7 = (float10)(lVar4 - lVar5) * extraout_ST0_00;
    fVar8 = extraout_ST0_00 * (float10)(lVar5 - local_8);
  }
  else {
    lVar5 = Terrain_Get_Height(unaff_EDI,unaff_ESI);
    fVar7 = (float10)(lVar5 - local_8) * extraout_ST0;
    fVar8 = extraout_ST0 * (float10)(lVar4 - lVar5);
  }
  local_20.x = (float)fVar7;
  local_20.z = (float)fVar8;
  local_20.y = 1.0;
  pVVar6 = Normalize_Vector(&local_2c,&local_20);
  __return_storage_ptr__->x = pVVar6->x;
  __return_storage_ptr__->y = pVVar6->y;
  __return_storage_ptr__->z = pVVar6->z;
  return __return_storage_ptr__;
}
