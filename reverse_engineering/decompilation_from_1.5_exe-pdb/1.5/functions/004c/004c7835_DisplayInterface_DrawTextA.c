/*
 * Entry: 004c7835
 * Name: DisplayInterface::DrawTextA
 * Namespace: DisplayInterface
 * Signature: void DrawTextA(char * param_1, long param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DisplayInterface::DrawTextA(char *param_1,long param_2,long param_3)

{
  long local_c;
  int local_8;
  
  Graphic_Text(currentBuffer,textLeft,textTop,&local_c,&local_8,param_1,textFont,param_2,param_3,0,0
               ,0);
  textTop = local_8 + 2;
  return;
}
