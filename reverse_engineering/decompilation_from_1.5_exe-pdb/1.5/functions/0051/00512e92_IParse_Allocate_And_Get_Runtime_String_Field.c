/*
 * Entry: 00512e92
 * Name: IParse_Allocate_And_Get_Runtime_String_Field
 * Namespace: Global
 * Signature: char * IParse_Allocate_And_Get_Runtime_String_Field(void * param_1, char * param_2, int * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl
IParse_Allocate_And_Get_Runtime_String_Field(void *param_1,char *param_2,int *param_3)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  int iVar4;
  
  pcVar2 = IParse_Get_Runtime_Struct_Field(param_1,param_2);
  if (pcVar2 != (char *)0x0) {
    pcVar3 = pcVar2;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    pcVar3 = calloc(1,(size_t)(pcVar3 + (1 - (int)(pcVar2 + 1))));
    if (pcVar3 != (char *)0x0) {
      *param_3 = 0;
      iVar4 = (int)pcVar3 - (int)pcVar2;
      do {
        cVar1 = *pcVar2;
        pcVar2[iVar4] = cVar1;
        pcVar2 = pcVar2 + 1;
      } while (cVar1 != '\0');
      return pcVar3;
    }
  }
  *param_3 = -1;
  return (char *)0x0;
}
