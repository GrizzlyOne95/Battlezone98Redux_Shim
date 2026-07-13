/*
 * Entry: 004e2f18
 * Name: NetUtil_ExpandMatrix
 * Namespace: Global
 * Signature: MAT_3D * NetUtil_ExpandMatrix(MAT_3D * __return_storage_ptr__, REDUCED_MAT param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

MAT_3D * __cdecl NetUtil_ExpandMatrix(MAT_3D *__return_storage_ptr__,REDUCED_MAT param_1)

{
  float fVar1;
  MAT_3D *pMVar2;
  int iVar3;
  QUAT *unaff_EDI;
  MAT_3D *pMVar4;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  float10 extraout_ST0_02;
  MAT_3D local_6c;
  QUAT local_2c;
  int local_1c;
  uchar local_18 [4];
  uchar auStack_14 [4];
  uchar auStack_10 [4];
  uchar auStack_c [4];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_18[0] = param_1.buf[0];
  local_18[1] = param_1.buf[1];
  local_18[2] = param_1.buf[2];
  local_18[3] = param_1.buf[3];
  auStack_14[0] = param_1.buf[4];
  auStack_14[1] = param_1.buf[5];
  auStack_14[2] = param_1.buf[6];
  auStack_14[3] = param_1.buf[7];
  auStack_10[0] = param_1.buf[8];
  auStack_10[1] = param_1.buf[9];
  auStack_10[2] = param_1.buf[10];
  auStack_10[3] = param_1.buf[0xb];
  auStack_c[0] = param_1.buf[0xc];
  auStack_c[1] = param_1.buf[0xd];
  local_1c = GetSignedFromBitfield(local_18,0,0xf);
  local_2c.n.x = (float)local_1c * 6.103888e-05;
  local_1c = GetSignedFromBitfield(local_18,0xf,0xf);
  local_2c.n.y = (float)((float10)local_1c * extraout_ST0);
  local_1c = GetSignedFromBitfield(local_18,0x1e,0xf);
  local_2c.n.z = (float)(extraout_ST0_00 * (float10)local_1c);
  fVar1 = ((1.0 - local_2c.n.x * local_2c.n.x) - local_2c.n.y * local_2c.n.y) -
          local_2c.n.z * local_2c.n.z;
  local_2c.w = 0.0;
  if (0.0 < fVar1) {
    local_2c.w = SQRT(fVar1);
  }
  NormalizeQuat(&local_2c);
  pMVar2 = Quaternion_to_Matrix(&local_6c,unaff_EDI);
  pMVar4 = __return_storage_ptr__;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    pMVar4->right_x = pMVar2->right_x;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
    pMVar4 = (MAT_3D *)&pMVar4->right_y;
  }
  local_1c = GetSignedFromBitfield(local_18,0x2d,0x18);
  __return_storage_ptr__->posit_x = (double)local_1c * 0.0009765625;
  local_1c = GetUnsignedFromBitfield(local_18,0x45,0x13);
  __return_storage_ptr__->posit_y = (double)((float10)local_1c * extraout_ST0_01);
  iVar3 = GetSignedFromBitfield(local_18,0x58,0x18);
  __return_storage_ptr__->posit_z = (double)((float10)iVar3 * extraout_ST0_02);
  __return_storage_ptr__->posit_x =
       (double)((TerMaxX + TerMinX) * 0.5 + (float)__return_storage_ptr__->posit_x);
  __return_storage_ptr__->posit_y = (double)(TerMinY + (float)__return_storage_ptr__->posit_y);
  __return_storage_ptr__->posit_z =
       (double)((TerMaxZ + TerMinZ) * 0.5 + (float)__return_storage_ptr__->posit_z);
  return __return_storage_ptr__;
}
