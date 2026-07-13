/*
 * Entry: 0054d3aa
 * Name: Mono_Display
 * Namespace: Global
 * Signature: void Mono_Display(long param_1, char * param_2, short param_3, short param_4, short param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Mono_Display(long param_1,char *param_2,short param_3,short param_4,short param_5)

{
  char cVar1;
  char *pcVar2;
  SHORT SStack00000012;
  DWORD local_8;
  
  if ((((-1 < param_4 - start_line) && (param_4 - start_line < 0x18)) && (param_1 != 0)) &&
     (param_1 == active_screen)) {
    SStack00000012 = param_4 - (short)start_line;
    param_4 = param_3;
    SetConsoleTextAttribute(console_out,param_5);
    pcVar2 = param_2;
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    WriteConsoleOutputCharacterA
              (console_out,param_2,(int)pcVar2 - (int)(param_2 + 1),_param_4,&local_8);
  }
  return;
}
