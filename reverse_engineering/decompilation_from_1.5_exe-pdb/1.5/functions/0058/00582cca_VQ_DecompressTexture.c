/*
 * Entry: 00582cca
 * Name: VQ_DecompressTexture
 * Namespace: Global
 * Signature: int VQ_DecompressTexture(VQTEXTURE * param_1, VQCODEBOOK * param_2, TEXTURE * param_3, ulong param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
VQ_DecompressTexture(VQTEXTURE *param_1,VQCODEBOOK *param_2,TEXTURE *param_3,ulong param_4)

{
  ushort *puVar1;
  PVECTOR *unaff_ESI;
  ulong unaff_EDI;
  ulong unaff_retaddr;
  
  if (param_4 < (uint)param_1->wide * param_1->high + 0x18) {
    return 0;
  }
  param_3->type = param_1->type;
  param_3->width = param_1->wide;
  puVar1 = (ushort *)param_1->high;
  param_3->height = (long)puVar1;
  decode_map((uchar *)(param_3 + 1),puVar1,(ulong)(param_2 + 1),unaff_EDI,unaff_ESI,unaff_retaddr);
  return 1;
}
