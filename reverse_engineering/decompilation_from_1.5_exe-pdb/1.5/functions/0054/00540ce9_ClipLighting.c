/*
 * Entry: 00540ce9
 * Name: ClipLighting
 * Namespace: Global
 * Signature: void ClipLighting(tagLIGHTING * param_1, tagLIGHTING * param_2, tagLIGHTING * param_3, float param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
ClipLighting(tagLIGHTING *param_1,tagLIGHTING *param_2,tagLIGHTING *param_3,float param_4)

{
  undefined1 extraout_AL;
  undefined1 extraout_AL_00;
  int *unaff_EBX;
  int *unaff_ESI;
  int *unaff_EDI;
  
  if (*unaff_ESI == *unaff_EDI) {
    *unaff_EBX = *unaff_ESI;
    return;
  }
  _ftol2();
  *(undefined1 *)unaff_EBX = extraout_AL;
  _ftol2();
  *(undefined1 *)((int)unaff_EBX + 1) = extraout_AL_00;
  return;
}
