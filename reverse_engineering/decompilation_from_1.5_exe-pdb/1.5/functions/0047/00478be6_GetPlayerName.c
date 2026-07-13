/*
 * Entry: 00478be6
 * Name: GetPlayerName
 * Namespace: Global
 * Signature: void GetPlayerName(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GetPlayerName(char *param_1)

{
  char cVar1;
  char *pcVar2;
  
  pcVar2 = player_name;
  do {
    cVar1 = *pcVar2;
    (param_1 + -0xa0f1d0)[(int)pcVar2] = cVar1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  return;
}
