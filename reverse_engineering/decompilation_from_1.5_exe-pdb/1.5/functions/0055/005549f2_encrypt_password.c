/*
 * Entry: 005549f2
 * Name: encrypt_password
 * Namespace: Global
 * Signature: void encrypt_password(char * param_1, char * param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl encrypt_password(char *param_1,char *param_2,char *param_3)

{
  uchar uVar1;
  char cVar2;
  uchar *puVar3;
  ulong uVar4;
  uchar *in_ECX;
  char *pcVar5;
  char *unaff_EDI;
  
  if (*in_ECX == '\0') {
    *unaff_EDI = '\0';
    return;
  }
  puVar3 = in_ECX;
  do {
    uVar1 = *puVar3;
    puVar3 = puVar3 + 1;
  } while (uVar1 != '\0');
  uVar4 = crc32seed(in_ECX,(int)puVar3 - (int)(in_ECX + 1),0x2a);
  if (param_1 != (char *)0x0) {
    pcVar5 = param_1;
    do {
      cVar2 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar2 != '\0');
    uVar4 = crc32seed((uchar *)param_1,(int)pcVar5 - (int)(param_1 + 1),uVar4);
  }
  _snprintf(unaff_EDI,10,"%x",uVar4);
  return;
}
