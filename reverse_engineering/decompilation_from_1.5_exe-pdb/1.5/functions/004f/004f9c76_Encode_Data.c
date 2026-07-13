/*
 * Entry: 004f9c76
 * Name: Encode_Data
 * Namespace: Global
 * Signature: void Encode_Data(_iobuf * param_1, char param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Encode_Data(_iobuf *param_1,char param_2,long param_3)

{
  uint in_EAX;
  
  if ((in_EAX == 1) && ((param_2 & 0xc0U) != 0xc0)) {
    fputc((int)param_2,(FILE *)param_1);
    return;
  }
  fputc(in_EAX | 0xc0,(FILE *)param_1);
  fputc((int)param_2,(FILE *)param_1);
  return;
}
