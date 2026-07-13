/*
 * Entry: 004f3f89
 * Name: Font_Get_String_Height
 * Namespace: Global
 * Signature: long Font_Get_String_Height(FONT * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Font_Get_String_Height(FONT *param_1,char *param_2)

{
  long local_8;
  
  Font_Get_String_Dimensions(param_1,param_2,(long *)0x0,&local_8);
  return local_8;
}
