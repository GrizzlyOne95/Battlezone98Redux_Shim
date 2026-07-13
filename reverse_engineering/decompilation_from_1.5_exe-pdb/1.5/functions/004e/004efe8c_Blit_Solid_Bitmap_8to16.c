/*
 * Entry: 004efe8c
 * Name: Blit_Solid_Bitmap_8to16
 * Namespace: Global
 * Signature: void Blit_Solid_Bitmap_8to16(ushort * param_1, uchar * param_2, long param_3, long param_4, long param_5, long param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Blit_Solid_Bitmap_8to16
          (ushort *param_1,uchar *param_2,long param_3,long param_4,long param_5,long param_6)

{
  int in_EAX;
  int iVar1;
  int in_ECX;
  int in_EDX;
  
  if (0 < in_EAX) {
    do {
      iVar1 = 0;
      if (0 < (int)param_1) {
        do {
          *(ushort *)(in_ECX + iVar1 * 2) = D3D_Remap_Palette[*(byte *)(iVar1 + in_EDX)];
          iVar1 = iVar1 + 1;
        } while (iVar1 < (int)param_1);
      }
      in_EDX = in_EDX + param_3;
      in_ECX = in_ECX + (int)param_2 * 2;
      in_EAX = in_EAX + -1;
    } while (in_EAX != 0);
  }
  return;
}
