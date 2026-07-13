/*
 * Entry: 004e3078
 * Name: NetUtil_ReduceMatrix
 * Namespace: Global
 * Signature: REDUCED_MAT * NetUtil_ReduceMatrix(REDUCED_MAT * __return_storage_ptr__, MAT_3D param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

REDUCED_MAT * __cdecl NetUtil_ReduceMatrix(REDUCED_MAT *__return_storage_ptr__,MAT_3D param_1)

{
  float fVar1;
  float fVar2;
  QUAT *pQVar3;
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int extraout_EAX_02;
  int extraout_EAX_03;
  int extraout_EAX_04;
  MAT_3D *unaff_EDI;
  REDUCED_MAT *pRVar4;
  uint uVar5;
  uint uVar6;
  QUAT local_24;
  QUAT local_14;
  
  pQVar3 = Matrix_to_Quaternion(&local_24,unaff_EDI);
  local_14.n.x = (pQVar3->n).x;
  local_14.n.y = (pQVar3->n).y;
  local_14.n.z = (pQVar3->n).z;
  local_14.w = pQVar3->w;
  NormalizeQuat(&local_14);
  if (local_14.w < 0.0) {
    local_14.w = -local_14.w;
    local_14.n.x = -local_14.n.x;
    local_14.n.y = -local_14.n.y;
    local_14.n.z = -local_14.n.z;
  }
  uVar6 = 0xf;
  uVar5 = 0;
  pRVar4 = __return_storage_ptr__;
  _ftol2_sse();
  AddSignedToBitfield(extraout_EAX,pRVar4,uVar5,uVar6);
  uVar6 = 0xf;
  uVar5 = 0xf;
  pRVar4 = __return_storage_ptr__;
  _ftol2_sse();
  AddSignedToBitfield(extraout_EAX_00,pRVar4,uVar5,uVar6);
  uVar6 = 0xf;
  uVar5 = 0x1e;
  pRVar4 = __return_storage_ptr__;
  _ftol2_sse();
  AddSignedToBitfield(extraout_EAX_01,pRVar4,uVar5,uVar6);
  uVar6 = 0x18;
  uVar5 = 0x2d;
  fVar2 = (float)(double)param_1._44_8_ - TerMinY;
  fVar1 = TerMaxZ + TerMinZ;
  pRVar4 = __return_storage_ptr__;
  floor((double)((float)(double)param_1._36_8_ - (TerMaxX + TerMinX) * 0.5) * 1024.0 + 0.5);
  _ftol2_sse();
  AddSignedToBitfield(extraout_EAX_02,pRVar4,uVar5,uVar6);
  uVar6 = 0x13;
  uVar5 = 0x45;
  pRVar4 = __return_storage_ptr__;
  floor((double)fVar2 * 1024.0 + 0.5);
  _ftol2_sse();
  AddUnsignedToBitfield(extraout_EAX_03,pRVar4,uVar5,uVar6);
  uVar6 = 0x18;
  uVar5 = 0x58;
  pRVar4 = __return_storage_ptr__;
  floor((double)((float)(double)param_1._52_8_ - fVar1 * 0.5) * 1024.0 + 0.5);
  _ftol2_sse();
  AddSignedToBitfield(extraout_EAX_04,pRVar4,uVar5,uVar6);
  return __return_storage_ptr__;
}
