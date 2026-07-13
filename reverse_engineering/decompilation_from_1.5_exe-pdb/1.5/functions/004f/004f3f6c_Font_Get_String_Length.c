/*
 * Entry: 004f3f6c
 * Name: Font_Get_String_Length
 * Namespace: Global
 * Signature: long Font_Get_String_Length(FONT * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Font_Get_String_Length(FONT *param_1,char *param_2)

{
  long local_8;
  
  Font_Get_String_Dimensions(param_1,param_2,&local_8,(long *)0x0);
  return local_8;
}
