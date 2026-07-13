/*
 * Entry: 005443b1
 * Name: D3D_Load_Texture_To_Entry
 * Namespace: Global
 * Signature: int D3D_Load_Texture_To_Entry(D3DCACHEENTRY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl D3D_Load_Texture_To_Entry(D3DCACHEENTRY *param_1)

{
  int *piVar1;
  _D3DFORMAT _Var2;
  int unaff_EBX;
  _D3DSURFACE_DESC *unaff_ESI;
  D3DCACHEENTRY *unaff_EDI;
  int iVar3;
  D3DCACHEENTRY *in_stack_ffffffd4;
  undefined1 local_c [8];
  
  piVar1 = *(int **)(unaff_EBX + 0xc);
  iVar3 = 0;
  _Var2 = GetTextureFormat(unaff_EDI);
  if (_Var2 != D3DFMT_UNKNOWN) {
    iVar3 = (**(code **)(*piVar1 + 0x44))(piVar1,0,&stack0xffffffd4);
    if (iVar3 == 0) {
      iVar3 = (**(code **)(*piVar1 + 0x4c))(piVar1,0,local_c,0,0x2000);
      if (iVar3 == 0) {
        iVar3 = Copy_Texture_To_D3D((_D3DLOCKED_RECT *)unaff_EDI,unaff_ESI,in_stack_ffffffd4);
        if (iVar3 == 0) {
          (**(code **)(*piVar1 + 0x50))(piVar1,0);
        }
      }
    }
  }
  D3DAppErrorToString(iVar3);
  D3D_DEBUG_systemWarning("%s");
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1);
  }
  return 0;
}
