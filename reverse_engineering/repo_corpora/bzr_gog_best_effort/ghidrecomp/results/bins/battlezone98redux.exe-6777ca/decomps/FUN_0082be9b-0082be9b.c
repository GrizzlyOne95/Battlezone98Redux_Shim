
void FUN_0082be9b(undefined4 param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  char *pcVar4;
  undefined4 local_210;
  FILE *local_20c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_0082c8f6(param_1);
  local_210 = 0;
  iVar1 = iVar1 + 1;
  if (param_2 == (char *)0x0) {
    FUN_0082cd08(param_1,"=stdin",6);
    local_20c = __iob_func();
LAB_0082beec:
    iVar2 = getc(local_20c);
    if (iVar2 == 0x23) {
      local_210 = 1;
      do {
        iVar2 = getc(local_20c);
        if (iVar2 == -1) break;
      } while (iVar2 != 10);
      if (iVar2 == 10) {
        iVar2 = getc(local_20c);
      }
    }
    if ((iVar2 == 0x1b) && (param_2 != (char *)0x0)) {
      local_20c = freopen(param_2,"rb",local_20c);
      if (local_20c == (FILE *)0x0) {
        pcVar4 = "reopen";
        goto LAB_0082bf93;
      }
      do {
        iVar2 = getc(local_20c);
        if (iVar2 == -1) break;
      } while (iVar2 != 0x1b);
      local_210 = 0;
    }
    ungetc(iVar2,local_20c);
    uVar3 = FUN_0082d377(param_1,0xffffffff,0);
    FUN_0082ca58(param_1,FUN_0082b77d,&local_210,uVar3);
    iVar2 = ferror(local_20c);
    if (param_2 != (char *)0x0) {
      fclose(local_20c);
    }
    if (iVar2 == 0) {
      FUN_0082cf99(param_1,iVar1);
    }
    else {
      FUN_0082d226();
      FUN_0082b735(param_1,&DAT_0086eaa0,iVar1);
    }
  }
  else {
    FUN_0082cc9e(param_1,&DAT_0086ea94,param_2);
    local_20c = fopen(param_2,"r");
    if (local_20c != (FILE *)0x0) goto LAB_0082beec;
    pcVar4 = "open";
LAB_0082bf93:
    FUN_0082b735(param_1,pcVar4,iVar1);
  }
  FUN_0083e885();
  return;
}

