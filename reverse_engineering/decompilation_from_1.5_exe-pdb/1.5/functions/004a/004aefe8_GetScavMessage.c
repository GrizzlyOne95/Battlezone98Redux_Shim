/*
 * Entry: 004aefe8
 * Name: GetScavMessage
 * Namespace: Global
 * Signature: void GetScavMessage(char * param_1, char param_2, char param_3, char param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GetScavMessage(char *param_1,char param_2,char param_3,char param_4)

{
  char in_AL;
  int iVar1;
  char *unaff_ESI;
  
  if (*unaff_ESI == '\0') {
    sprintf(unaff_ESI,"%cvscav%c.wav",(int)(char)param_1,(int)in_AL);
    iVar1 = ItemExists(unaff_ESI);
    if (iVar1 == 0) {
      *unaff_ESI = param_2;
    }
  }
  return;
}
