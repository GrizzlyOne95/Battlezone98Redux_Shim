
/* WARNING: Removing unreachable block (ram,0x004cd6e9) */

undefined1 FUN_004cd670(FILE *param_1,int param_2,uint param_3,undefined4 param_4)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  int local_10;
  undefined1 local_5;
  
  if (DAT_009173b6 == '\0') {
    FUN_004cc410(1,1,10,param_3);
    iVar3 = fprintf(param_1,"%s [%d] =\r\n",param_4,param_3 >> 3);
    for (local_10 = 0; local_10 < (int)(param_3 >> 3); local_10 = local_10 + 1) {
      cVar2 = FUN_004cd360(param_1,param_2 + local_10 * 8,4,&DAT_00879710,iVar3);
      if ((cVar2 == '\0') ||
         (cVar2 = FUN_004cd360(param_1,param_2 + 4 + local_10 * 8,4,&DAT_00879704,iVar3),
         cVar2 == '\0')) {
        bVar1 = false;
      }
      else {
        bVar1 = true;
      }
      if (!bVar1) {
        return 0;
      }
    }
    local_5 = 1;
  }
  else {
    local_5 = FUN_004ccae0(param_1,10,param_3,param_2);
  }
  return local_5;
}

