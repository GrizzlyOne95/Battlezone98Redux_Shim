/*
 * Entry: 004f9cbd
 * Name: Encode_Scan_Line
 * Namespace: Global
 * Signature: void Encode_Scan_Line(_iobuf * param_1, char * param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Encode_Scan_Line(_iobuf *param_1,char *param_2,long param_3)

{
  char cVar1;
  char *in_EAX;
  int iVar2;
  int in_ECX;
  long unaff_ESI;
  long unaff_EDI;
  int iVar3;
  char local_8;
  
  local_8 = *in_EAX;
  iVar2 = 1;
  if (1 < in_ECX) {
    iVar3 = in_ECX + -1;
    do {
      in_EAX = in_EAX + 1;
      cVar1 = *in_EAX;
      if (cVar1 == local_8) {
        iVar2 = iVar2 + 1;
        if (iVar2 == 0x3f) {
          Encode_Data(param_1,local_8,unaff_EDI);
          iVar2 = 0;
        }
      }
      else {
        if (iVar2 != 0) {
          Encode_Data(param_1,local_8,unaff_EDI);
        }
        iVar2 = 1;
        local_8 = cVar1;
      }
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    if (iVar2 == 0) {
      return;
    }
  }
  Encode_Data(param_1,local_8,unaff_ESI);
  return;
}
