
void FUN_005c2d60(char *param_1,char param_2,char param_3,char param_4)

{
  int iVar1;
  
  if (*param_1 == '\0') {
    sprintf(param_1,"%cvscav%c.wav",(int)param_2,(int)param_4);
    iVar1 = FUN_00481f10(param_1);
    if (iVar1 == 0) {
      *param_1 = param_3;
    }
  }
  return;
}

