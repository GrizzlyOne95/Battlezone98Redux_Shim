/*
 * Entry: 004e3376
 * Name: NetUtil_ExpandMatNoRoll
 * Namespace: Global
 * Signature: MAT_3D * NetUtil_ExpandMatNoRoll(MAT_3D * __return_storage_ptr__, RMAT param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

MAT_3D * __cdecl NetUtil_ExpandMatNoRoll(MAT_3D *__return_storage_ptr__,RMAT param_1)

{
  MAT_3D *pMVar1;
  int iVar2;
  VECTOR_3D *unaff_ESI;
  VECTOR_3D *unaff_EDI;
  MAT_3D *pMVar3;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  float10 fVar4;
  float10 fVar5;
  unkbyte10 extraout_ST1;
  MAT_3D local_70;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  int local_18;
  uchar local_14 [4];
  uchar auStack_10 [4];
  uchar auStack_c [4];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_14[0] = param_1.buf[0];
  local_14[1] = param_1.buf[1];
  local_14[2] = param_1.buf[2];
  local_14[3] = param_1.buf[3];
  auStack_10[0] = param_1.buf[4];
  auStack_10[1] = param_1.buf[5];
  auStack_10[2] = param_1.buf[6];
  auStack_10[3] = param_1.buf[7];
  auStack_c[0] = param_1.buf[8];
  auStack_c[1] = param_1.buf[9];
  local_18 = GetSignedFromBitfield(local_14,0,0x14);
  local_24 = (float)local_18 * 0.015625;
  local_18 = GetUnsignedFromBitfield(local_14,0x14,0xf);
  local_20 = (float)((float10)local_18 * extraout_ST0);
  local_18 = GetSignedFromBitfield(local_14,0x23,0x14);
  local_24 = (float)(((float10)TerMaxX + (float10)TerMinX) * (float10)0.5 + (float10)local_24);
  local_20 = TerMinY + local_20;
  local_1c = (float)(((float10)TerMaxZ + (float10)TerMinZ) * (float10)0.5 +
                    extraout_ST0_00 * (float10)local_18);
  local_18 = GetSignedFromBitfield(local_14,0x37,0xd);
  local_18 = GetSignedFromBitfield(local_14,0x44,0xc);
  fVar4 = (float10)fcos(extraout_ST0_01 * (float10)local_18);
  fVar5 = (float10)fsin(extraout_ST1);
  local_30 = (float)(fVar5 * fVar4);
  fVar5 = (float10)fsin(extraout_ST0_01 * (float10)local_18);
  local_2c = (float)-fVar5;
  fVar5 = (float10)fcos(extraout_ST1);
  local_28 = (float)(fVar5 * fVar4);
  pMVar1 = Build_Directinal_Matrix(&local_70,unaff_EDI,unaff_ESI);
  pMVar3 = __return_storage_ptr__;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    pMVar3->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
  }
  return __return_storage_ptr__;
}
