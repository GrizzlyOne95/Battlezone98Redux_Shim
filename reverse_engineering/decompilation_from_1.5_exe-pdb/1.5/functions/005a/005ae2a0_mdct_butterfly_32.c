/*
 * Entry: 005ae2a0
 * Name: mdct_butterfly_32
 * Namespace: Global
 * Signature: void mdct_butterfly_32(float * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl mdct_butterfly_32(float *param_1)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float *pfVar5;
  float *in_EAX;
  
  fVar2 = in_EAX[0x1e];
  fVar3 = in_EAX[0x1f];
  in_EAX[0x1e] = in_EAX[0x1e] + in_EAX[0xe];
  in_EAX[0x1f] = in_EAX[0x1f] + in_EAX[0xf];
  in_EAX[0xe] = fVar2 - in_EAX[0xe];
  in_EAX[0xf] = fVar3 - in_EAX[0xf];
  fVar2 = in_EAX[0x1c];
  fVar3 = in_EAX[0xc];
  fVar4 = in_EAX[0x1d];
  in_EAX[0x1c] = in_EAX[0x1c] + in_EAX[0xc];
  in_EAX[0x1d] = in_EAX[0x1d] + in_EAX[0xd];
  in_EAX[0xc] = (fVar2 - fVar3) * 0.9238795 - (fVar4 - in_EAX[0xd]) * 0.38268343;
  in_EAX[0xd] = (fVar2 - fVar3) * 0.38268343 + (fVar4 - in_EAX[0xd]) * 0.9238795;
  fVar2 = in_EAX[0x1a];
  fVar3 = in_EAX[10];
  fVar4 = in_EAX[0x1b];
  in_EAX[0x1a] = in_EAX[0x1a] + in_EAX[10];
  in_EAX[0x1b] = in_EAX[0x1b] + in_EAX[0xb];
  in_EAX[10] = ((fVar2 - fVar3) - (fVar4 - in_EAX[0xb])) * 0.70710677;
  in_EAX[0xb] = ((fVar4 - in_EAX[0xb]) + (fVar2 - fVar3)) * 0.70710677;
  fVar2 = in_EAX[0x18];
  fVar3 = in_EAX[8];
  fVar4 = in_EAX[0x19];
  in_EAX[0x18] = in_EAX[0x18] + in_EAX[8];
  in_EAX[0x19] = in_EAX[0x19] + in_EAX[9];
  in_EAX[8] = (fVar2 - fVar3) * 0.38268343 - (fVar4 - in_EAX[9]) * 0.9238795;
  in_EAX[9] = (fVar2 - fVar3) * 0.9238795 + (fVar4 - in_EAX[9]) * 0.38268343;
  fVar2 = in_EAX[0x16];
  fVar3 = in_EAX[6];
  fVar4 = in_EAX[0x17];
  in_EAX[0x16] = in_EAX[0x16] + in_EAX[6];
  in_EAX[0x17] = in_EAX[0x17] + in_EAX[7];
  in_EAX[6] = in_EAX[7] - fVar4;
  in_EAX[7] = fVar2 - fVar3;
  fVar2 = in_EAX[4];
  fVar3 = in_EAX[0x14];
  fVar4 = in_EAX[0x15];
  in_EAX[0x14] = in_EAX[0x14] + in_EAX[4];
  in_EAX[0x15] = in_EAX[0x15] + in_EAX[5];
  in_EAX[4] = (fVar2 - fVar3) * 0.38268343 + (in_EAX[5] - fVar4) * 0.9238795;
  in_EAX[5] = (in_EAX[5] - fVar4) * 0.38268343 - (fVar2 - fVar3) * 0.9238795;
  fVar2 = in_EAX[2];
  fVar3 = in_EAX[0x12];
  fVar4 = in_EAX[0x13];
  in_EAX[0x12] = in_EAX[0x12] + in_EAX[2];
  in_EAX[0x13] = in_EAX[0x13] + in_EAX[3];
  in_EAX[2] = ((fVar2 - fVar3) + (in_EAX[3] - fVar4)) * 0.70710677;
  in_EAX[3] = ((in_EAX[3] - fVar4) - (fVar2 - fVar3)) * 0.70710677;
  fVar2 = *in_EAX;
  pfVar1 = in_EAX + 0x10;
  fVar3 = *pfVar1;
  pfVar5 = (float *)(in_EAX[1] - in_EAX[0x11]);
  *pfVar1 = *pfVar1 + *in_EAX;
  in_EAX[0x11] = in_EAX[0x11] + in_EAX[1];
  *in_EAX = (fVar2 - fVar3) * 0.9238795 + (float)pfVar5 * 0.38268343;
  in_EAX[1] = (float)pfVar5 * 0.9238795 - (fVar2 - fVar3) * 0.38268343;
  mdct_butterfly_16(pfVar5);
  mdct_butterfly_16(param_1);
  return;
}
