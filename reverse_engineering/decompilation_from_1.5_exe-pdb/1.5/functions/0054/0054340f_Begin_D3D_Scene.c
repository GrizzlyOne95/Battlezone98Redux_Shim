/*
 * Entry: 0054340f
 * Name: Begin_D3D_Scene
 * Namespace: Global
 * Signature: int Begin_D3D_Scene(CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Begin_D3D_Scene(CAMERA *param_1)

{
  int iVar1;
  
  D3D_Video_Memory_Is_Dirty = 0;
  iVar1 = (*(d3dappi.lpD3DDevice)->lpVtbl->BeginScene)(d3dappi.lpD3DDevice);
  return (uint)(iVar1 == 0);
}
