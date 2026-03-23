
char * FUN_008358d9(int param_1,char *param_2)

{
  char *pcVar1;
  char *pcVar2;
  
  pcVar1 = param_2 + 1;
  if (*param_2 == '%') {
    pcVar2 = pcVar1;
    if (*pcVar1 == '\0') {
      FUN_0082bc39(*(undefined4 *)(param_1 + 8),"malformed pattern (ends with \'%%\')");
    }
  }
  else {
    if (*param_2 != '[') {
      return pcVar1;
    }
    if (*pcVar1 == '^') {
      pcVar1 = param_2 + 2;
    }
    do {
      if (*pcVar1 == '\0') {
        FUN_0082bc39(*(undefined4 *)(param_1 + 8),"malformed pattern (missing \']\')");
      }
      pcVar2 = pcVar1 + 1;
      if ((*pcVar1 == '%') && (*pcVar2 != '\0')) {
        pcVar2 = pcVar1 + 2;
      }
      pcVar1 = pcVar2;
    } while (*pcVar2 != ']');
  }
  return pcVar2 + 1;
}

