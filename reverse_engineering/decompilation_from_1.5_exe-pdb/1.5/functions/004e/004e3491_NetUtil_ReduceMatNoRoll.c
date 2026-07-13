/*
 * Entry: 004e3491
 * Name: NetUtil_ReduceMatNoRoll
 * Namespace: Global
 * Signature: RMAT * NetUtil_ReduceMatNoRoll(RMAT * __return_storage_ptr__, MAT_3D param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RMAT * __cdecl NetUtil_ReduceMatNoRoll(RMAT *__return_storage_ptr__,MAT_3D param_1)

{
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  VECTOR_3D *pVVar1;
  int extraout_EAX_02;
  int extraout_EAX_03;
  float10 fVar2;
  float10 fVar4;
  RMAT *pRVar5;
  uint uVar6;
  uint uVar7;
  undefined1 local_20 [8];
  double local_18;
  VECTOR_3D local_10;
  float10 fVar3;
  
  local_10.x = param_1.up_z;
  local_10.y = param_1.front_x;
  local_10.z = param_1.front_y;
  uVar7 = 0x14;
  uVar6 = 0;
  local_20 = (undefined1  [8])((double)param_1._44_8_ - (double)TerMinY);
  local_18 = (double)param_1._52_8_ - ((double)TerMaxZ + (double)TerMinZ) * 0.5;
  pRVar5 = __return_storage_ptr__;
  floor(((double)param_1._36_8_ - ((double)TerMaxX + (double)TerMinX) * 0.5) * 64.0 + 0.5);
  _ftol2_sse();
  AddSignedToBitfield(extraout_EAX,pRVar5,uVar6,uVar7);
  uVar7 = 0xf;
  uVar6 = 0x14;
  pRVar5 = __return_storage_ptr__;
  floor((double)local_20 * 64.0 + 0.5);
  _ftol2_sse();
  AddUnsignedToBitfield(extraout_EAX_00,pRVar5,uVar6,uVar7);
  uVar7 = 0x14;
  uVar6 = 0x23;
  pRVar5 = __return_storage_ptr__;
  floor(local_18 * 64.0 + 0.5);
  _ftol2_sse();
  AddSignedToBitfield(extraout_EAX_01,pRVar5,uVar6,uVar7);
  pVVar1 = Normalize_Vector((VECTOR_3D *)(local_20 + 4),&local_10);
  fVar4 = (float10)1;
  local_10.x = pVVar1->x;
  local_10.y = pVVar1->y;
  local_10.z = pVVar1->z;
  fVar3 = (float10)local_10.x;
  if (fVar4 < (float10)local_10.x) {
    fVar3 = fVar4;
  }
  fVar2 = (float10)-1.0;
  if (fVar3 < fVar2) {
    fVar3 = fVar2;
  }
  if (fVar4 < (float10)local_10.y) {
    local_10.y = (float)fVar4;
  }
  if ((float10)local_10.y < fVar2) {
    local_10.y = (float)fVar2;
  }
  uVar7 = 0xd;
  fVar4 = (float10)fpatan(fVar3,(float10)local_10.z);
  uVar6 = 0x37;
  pRVar5 = __return_storage_ptr__;
  floor((double)(fVar4 * (float10)1303.479 + (float10)0.5));
  _ftol2_sse();
  AddSignedToBitfield(extraout_EAX_02,pRVar5,uVar6,uVar7);
  uVar7 = 0xc;
  uVar6 = 0x44;
  pRVar5 = __return_storage_ptr__;
  fVar4 = (float10)__CIasin();
  floor((double)(-fVar4 * (float10)1303.479 + (float10)0.5));
  _ftol2_sse();
  AddSignedToBitfield(extraout_EAX_03,pRVar5,uVar6,uVar7);
  return __return_storage_ptr__;
}
