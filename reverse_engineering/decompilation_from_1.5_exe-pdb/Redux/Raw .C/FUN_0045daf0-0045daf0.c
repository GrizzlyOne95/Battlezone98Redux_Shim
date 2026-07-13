
void __thiscall FUN_0045daf0(int param_1,undefined4 param_2,char *param_3,undefined1 param_4)

{
  char cVar1;
  char *local_10;
  
  *(undefined1 *)(param_1 + 0x10) = 1;
  *(undefined4 *)(param_1 + 0x14) = param_2;
  if (param_3 == (char *)0x0) {
    *(undefined4 *)(param_1 + 0x19) = 0;
    *(undefined4 *)(param_1 + 0x1d) = 0;
    *(undefined4 *)(param_1 + 0x21) = 0;
    *(undefined2 *)(param_1 + 0x25) = 0;
  }
  else {
    local_10 = param_3;
    do {
      cVar1 = *local_10;
      local_10 = local_10 + 1;
    } while (cVar1 != '\0');
    if (0xd < (uint)((int)local_10 - (int)(param_3 + 1))) {
      FUN_007d6c70("AiMission: file name \"%s\" is too long\nName must be less than %d characters\n"
                   ,param_3,0xe);
    }
    strncpy((char *)(param_1 + 0x19),param_3,0xd);
    *(undefined1 *)(param_1 + 0x26) = 0;
  }
  *(undefined1 *)(param_1 + 0x18) = param_4;
  return;
}

