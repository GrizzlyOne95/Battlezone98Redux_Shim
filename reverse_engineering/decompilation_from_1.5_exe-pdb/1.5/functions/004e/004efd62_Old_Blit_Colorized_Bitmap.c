/*
 * Entry: 004efd62
 * Name: Old_Blit_Colorized_Bitmap
 * Namespace: Global
 * Signature: void Old_Blit_Colorized_Bitmap(char * param_1, char * param_2, long param_3, long param_4, long param_5, long param_6, char param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Old_Blit_Colorized_Bitmap
          (char *param_1,char *param_2,long param_3,long param_4,long param_5,long param_6,
          char param_7)

{
  int in_EAX;
  byte *in_ECX;
  char *in_EDX;
  char *pcVar1;
  char *pcVar2;
  
  if (0 < in_EAX) {
    do {
      pcVar1 = (char *)0x0;
      pcVar2 = param_1;
      if (0 < (int)param_1) {
        do {
          if (*in_EDX != -1) {
            *in_ECX = (*in_EDX == '\0') - 1U & (byte)param_4;
          }
          in_EDX = in_EDX + 1;
          in_ECX = in_ECX + 1;
          pcVar2 = pcVar2 + -1;
          pcVar1 = param_1;
        } while (pcVar2 != (char *)0x0);
      }
      in_EDX = in_EDX + (param_3 - (int)pcVar1);
      in_ECX = in_ECX + ((int)param_2 - (int)pcVar1);
      in_EAX = in_EAX + -1;
    } while (in_EAX != 0);
  }
  return;
}
