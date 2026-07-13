/*
 * Entry: 004efec7
 * Name: Blit_Transparent_Bitmap_8to16
 * Namespace: Global
 * Signature: void Blit_Transparent_Bitmap_8to16(ushort * param_1, uchar * param_2, long param_3, long param_4, long param_5, long param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Blit_Transparent_Bitmap_8to16
          (ushort *param_1,uchar *param_2,long param_3,long param_4,long param_5,long param_6)

{
  int in_EAX;
  int iVar1;
  int in_ECX;
  int in_EDX;
  
  if (0 < in_EAX) {
    do {
      iVar1 = 0;
      if (0 < (int)param_2) {
        do {
          if (*(byte *)(iVar1 + in_ECX) != 0xff) {
            param_1[iVar1] = D3D_Remap_Palette[*(byte *)(iVar1 + in_ECX)];
          }
          iVar1 = iVar1 + 1;
        } while (iVar1 < (int)param_2);
      }
      in_ECX = in_ECX + param_3;
      param_1 = param_1 + in_EDX;
      in_EAX = in_EAX + -1;
    } while (in_EAX != 0);
  }
  return;
}
