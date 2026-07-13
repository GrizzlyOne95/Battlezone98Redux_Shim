
char * FUN_006b6270(undefined4 param_1)

{
  char *pcVar1;
  
  switch(param_1) {
  case 1:
    pcVar1 = "devel";
    break;
  case 2:
    pcVar1 = "library";
    break;
  default:
    pcVar1 = "unknown";
    break;
  case 4:
    pcVar1 = "info";
    break;
  case 8:
    pcVar1 = "warning";
    break;
  case 0x10:
    pcVar1 = "error";
    break;
  case 0x20:
    pcVar1 = "fatal";
  }
  return pcVar1;
}

