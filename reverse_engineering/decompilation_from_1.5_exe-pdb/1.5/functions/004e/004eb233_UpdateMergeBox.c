/*
 * Entry: 004eb233
 * Name: UpdateMergeBox
 * Namespace: Global
 * Signature: void UpdateMergeBox(tagENTITY * param_1, VECTOR_3D * param_2, tagENTITY * param_3, VECTOR_3D * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
UpdateMergeBox(tagENTITY *param_1,VECTOR_3D *param_2,tagENTITY *param_3,VECTOR_3D *param_4)

{
  float fVar1;
  float *in_EAX;
  int in_ECX;
  int in_EDX;
  float *unaff_ESI;
  
  if (in_EDX == 0) {
    *(float *)(in_ECX + 0xac) = *in_EAX - *(float *)(in_ECX + 0x14);
    *(float *)(in_ECX + 0xb8) = *in_EAX + *(float *)(in_ECX + 0x14);
    *(float *)(in_ECX + 0xb0) = in_EAX[1] - *(float *)(in_ECX + 0x14);
    *(float *)(in_ECX + 0xbc) = *(float *)(in_ECX + 0x14) + in_EAX[1];
    *(float *)(in_ECX + 0xb4) = in_EAX[2] - *(float *)(in_ECX + 0x14);
    fVar1 = *(float *)(in_ECX + 0x14) + in_EAX[2];
  }
  else {
    fVar1 = *unaff_ESI - *(float *)(in_EDX + 0x14);
    if (fVar1 < *(float *)(in_ECX + 0xac)) {
      *(float *)(in_ECX + 0xac) = fVar1;
    }
    fVar1 = *(float *)(in_EDX + 0x14) + *unaff_ESI;
    if (*(float *)(in_ECX + 0xb8) < fVar1) {
      *(float *)(in_ECX + 0xb8) = fVar1;
    }
    fVar1 = unaff_ESI[1] - *(float *)(in_EDX + 0x14);
    if (fVar1 < *(float *)(in_ECX + 0xb0)) {
      *(float *)(in_ECX + 0xb0) = fVar1;
    }
    fVar1 = *(float *)(in_EDX + 0x14) + unaff_ESI[1];
    if (*(float *)(in_ECX + 0xbc) < fVar1) {
      *(float *)(in_ECX + 0xbc) = fVar1;
    }
    fVar1 = unaff_ESI[2] - *(float *)(in_EDX + 0x14);
    if (fVar1 < *(float *)(in_ECX + 0xb4)) {
      *(float *)(in_ECX + 0xb4) = fVar1;
    }
    fVar1 = *(float *)(in_EDX + 0x14) + unaff_ESI[2];
    if (fVar1 <= *(float *)(in_ECX + 0xc0)) {
      return;
    }
  }
  *(float *)(in_ECX + 0xc0) = fVar1;
  return;
}
