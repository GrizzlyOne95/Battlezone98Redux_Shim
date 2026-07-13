/*
 * Entry: 00473594
 * Name: CheckEntityBoxes
 * Namespace: Global
 * Signature: int CheckEntityBoxes(tagENTITY * param_1, tagENTITY * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CheckEntityBoxes(tagENTITY *param_1,tagENTITY *param_2)

{
  int in_ECX;
  int in_EDX;
  
  if ((((*(float *)(in_EDX + 0x44) <= *(float *)(in_ECX + 0x50)) &&
       (*(float *)(in_ECX + 0x44) <= *(float *)(in_EDX + 0x50))) &&
      (*(float *)(in_EDX + 0x4c) <= *(float *)(in_ECX + 0x58))) &&
     (((*(float *)(in_ECX + 0x4c) <= *(float *)(in_EDX + 0x58) &&
       (*(float *)(in_EDX + 0x48) <= *(float *)(in_ECX + 0x54))) &&
      (*(float *)(in_ECX + 0x48) <= *(float *)(in_EDX + 0x54))))) {
    return 1;
  }
  return 0;
}
