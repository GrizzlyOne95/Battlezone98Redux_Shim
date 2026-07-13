
void FUN_00623810(int param_1,int param_2)

{
  uint uVar1;
  char *pcVar2;
  
  uVar1 = *(uint *)(param_2 + 0x60);
  pcVar2 = strstr((char *)(param_1 + 0xc),"Tracker");
  if (pcVar2 == (char *)0x0) {
    pcVar2 = strstr((char *)(param_1 + 0xc),"SideWinder");
    if ((pcVar2 == (char *)0x0) &&
       (((((uVar1 & 1) == 0 || ((uVar1 & 2) == 0)) || ((uVar1 & 0x10) == 0)) ||
        (((uVar1 & 0x20) == 0 || (*(int *)(param_2 + 0x3c) != 8)))))) {
      pcVar2 = strstr((char *)(param_1 + 0xc),"Flightstick Pro");
      if ((pcVar2 == (char *)0x0) &&
         ((((uVar1 & 1) == 0 || ((uVar1 & 0x10) == 0)) ||
          (((uVar1 & 0x20) == 0 || (*(int *)(param_2 + 0x3c) != 4)))))) {
        pcVar2 = strstr((char *)(param_1 + 0xc),"Thrustmaster");
        if ((pcVar2 == (char *)0x0) &&
           (((((uVar1 & 2) == 0 || ((uVar1 & 0x10) == 0)) || ((uVar1 & 0x20) == 0)) ||
            (*(int *)(param_2 + 0x3c) != 4)))) {
          builtin_strncpy((char *)(param_1 + 0x4c),"joys",4);
          builtin_strncpy((char *)(param_1 + 0x50),"tick",4);
          *(undefined1 *)(param_1 + 0x54) = 0;
        }
        else {
          builtin_strncpy((char *)(param_1 + 0x4c),"tmas",4);
          builtin_strncpy((char *)(param_1 + 0x50),"ter",4);
        }
      }
      else {
        builtin_strncpy((char *)(param_1 + 0x4c),"flts",4);
        builtin_strncpy((char *)(param_1 + 0x50),"tick",4);
        *(undefined1 *)(param_1 + 0x54) = 0;
      }
    }
    else {
      builtin_strncpy((char *)(param_1 + 0x4c),"side",4);
      builtin_strncpy((char *)(param_1 + 0x50),"wind",4);
      *(undefined1 *)(param_1 + 0x54) = 0;
    }
  }
  else {
    builtin_strncpy((char *)(param_1 + 0x4c),"trac",4);
    builtin_strncpy((char *)(param_1 + 0x50),"ker",4);
  }
  return;
}

