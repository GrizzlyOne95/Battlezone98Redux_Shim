/*
 * Entry: 004e9487
 * Name: Cache_Render_Bsp_Mesh
 * Namespace: Global
 * Signature: void Cache_Render_Bsp_Mesh(BSP_POLYGON * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */

void __cdecl Cache_Render_Bsp_Mesh(BSP_POLYGON *param_1)

{
  char *pcVar1;
  char *in_ECX;
  BSP_POLYGON *unaff_ESI;
  int iVar2;
  undefined4 auStack_1004 [511];
  float afStack_808 [512];
  undefined4 uStack_8;
  
  uStack_8 = 0x4e9494;
  if (in_ECX == (char *)0x0) {
    return;
  }
  iVar2 = 0;
  do {
    auStack_1004[iVar2] = in_ECX;
    iVar2 = iVar2 + 1;
    if (*in_ECX == '\0') {
      afStack_808[iVar2] =
           *(float *)(in_ECX + 0x18) * Test_Point.x +
           *(float *)(in_ECX + 0x1c) * Test_Point.y + *(float *)(in_ECX + 0x20) * Test_Point.z +
           *(float *)(in_ECX + 0x24);
    }
    else {
      afStack_808[iVar2] = 0.0;
    }
    if (0.0 <= afStack_808[iVar2]) {
      in_ECX = *(char **)(in_ECX + 0x2c);
    }
    else {
      in_ECX = *(char **)(in_ECX + 0x28);
    }
    while (in_ECX == (char *)0x0) {
      if (iVar2 == 0) {
        return;
      }
      pcVar1 = (char *)auStack_1004[iVar2 + -1];
      if (*pcVar1 == '\0') {
        if ((afStack_808[iVar2] < 0.0) && (pcVar1[1] != '\0')) {
          Cache_Render_Bsp_Poly(unaff_ESI);
        }
      }
      else {
        Cache_Render_Single_Geometry(unaff_ESI);
      }
      if (0.0 <= afStack_808[iVar2]) {
        in_ECX = *(char **)(pcVar1 + 0x28);
        iVar2 = iVar2 + -1;
      }
      else {
        in_ECX = *(char **)(pcVar1 + 0x2c);
        iVar2 = iVar2 + -1;
      }
    }
  } while( true );
}
