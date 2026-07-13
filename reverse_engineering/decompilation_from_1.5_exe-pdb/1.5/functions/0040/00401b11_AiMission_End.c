/*
 * Entry: 00401b11
 * Name: AiMission::End
 * Namespace: AiMission
 * Signature: void End(AiMission * this, float param_1, char * param_2, bool param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AiMission::End(AiMission *this,float param_1,char *param_2,bool param_3)

{
  char cVar1;
  char *pcVar2;
  
  this->shutdownTime = param_1;
  this->done = true;
  if (param_2 == (char *)0x0) {
    this->resultName[0] = '\0';
    this->resultName[1] = '\0';
    this->resultName[2] = '\0';
    this->resultName[3] = '\0';
    this->resultName[4] = '\0';
    this->resultName[5] = '\0';
    this->resultName[6] = '\0';
    this->resultName[7] = '\0';
    this->resultName[8] = '\0';
    this->resultName[9] = '\0';
    this->resultName[10] = '\0';
    this->resultName[0xb] = '\0';
    this->resultName[0xc] = '\0';
    this->resultName[0xd] = '\0';
  }
  else {
    pcVar2 = param_2;
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    if (0xd < (uint)((int)pcVar2 - (int)(param_2 + 1))) {
      TraceError("AiMission: file name \"%s\" is too long\nName must be less than %d characters\n");
    }
    strncpy(this->resultName,param_2,0xd);
    this->resultName[0xd] = '\0';
  }
  this->failed = param_3;
  return;
}
