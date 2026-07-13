/*
 * Entry: 004b2281
 * Name: VQ_GetSize
 * Namespace: Global
 * Signature: ulong VQ_GetSize(VQTEXTURE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong __cdecl VQ_GetSize(VQTEXTURE *param_1)

{
  return (uint)param_1->wide * param_1->high + 0x18;
}
