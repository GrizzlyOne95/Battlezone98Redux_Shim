
/* WARNING: Removing unreachable block (ram,0x004ccff0) */
/* WARNING: Removing unreachable block (ram,0x004ccf96) */

undefined1 FUN_004ccf20(FILE *param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  char *pcVar2;
  int local_10;
  undefined1 local_5;
  
  if (DAT_009173b6 == '\0') {
    FUN_004cc410(1,0,1,param_3);
    iVar1 = fprintf(param_1,"%s [%d] =\r\n",param_4,param_3);
    for (local_10 = 0; local_10 < param_3; local_10 = local_10 + 1) {
      if (*(char *)(param_2 + local_10) == '\0') {
        pcVar2 = "false";
      }
      else {
        pcVar2 = "true";
      }
      iVar1 = fprintf(param_1,"%s\r\n",pcVar2,pcVar2,iVar1);
    }
    local_5 = 1;
  }
  else {
    local_5 = FUN_004ccbd0(param_1,1,param_3,param_2);
  }
  return local_5;
}

