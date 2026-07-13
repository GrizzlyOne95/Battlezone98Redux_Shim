/*
 * Entry: 004f4887
 * Name: Graphic_Buffer_Close
 * Namespace: Global
 * Signature: void Graphic_Buffer_Close(_GRAPHIC_BUFFER * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Graphic_Buffer_Close(_GRAPHIC_BUFFER *param_1)

{
  if (param_1->Status == 1) {
    if ((param_1->Allocated != 1) && (param_1->OrBuffer != (uchar *)0x0)) {
      free(param_1->OrBuffer);
    }
    param_1->Buffer = (uchar *)0x0;
    param_1->OrBuffer = (uchar *)0x0;
    param_1->Allocated = 1;
  }
  return;
}
