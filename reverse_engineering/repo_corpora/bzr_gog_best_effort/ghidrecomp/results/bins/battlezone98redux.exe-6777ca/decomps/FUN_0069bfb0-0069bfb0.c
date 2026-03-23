
char * FUN_0069bfb0(undefined4 param_1,char *param_2)

{
  switch(param_1) {
  case 5:
    param_2[0] = '}';
    param_2[1] = ';';
    param_2[2] = '\0';
    break;
  default:
    param_2[0] = ';';
    param_2[1] = '\0';
    break;
  case 7:
    param_2[0] = '\n';
    param_2[1] = '\0';
    break;
  case 8:
    builtin_strncpy(param_2,"#END_DATA",10);
    break;
  case 0xb:
    param_2[0] = ')';
    param_2[1] = '\0';
    break;
  case 0xc:
    param_2[0] = ')';
    param_2[1] = '\0';
    break;
  case 0xd:
    param_2[0] = '}';
    param_2[1] = '\0';
    break;
  case 0x10:
    param_2[0] = '\n';
    param_2[1] = '\0';
  }
  return param_2;
}

