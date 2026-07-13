
/* WARNING: Removing unreachable block (ram,0x004cd505) */
/* WARNING: Removing unreachable block (ram,0x004cd4b9) */

undefined1 FUN_004cd440(FILE *param_1,int param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  int local_10;
  undefined1 local_5;
  
  if (DAT_009173b6 == '\0') {
    FUN_004cc410(1,0,6,param_3);
    iVar1 = fprintf(param_1,"%s [%d] =\r\n",param_4,param_3 >> 3);
    for (local_10 = 0; local_10 < (int)(param_3 >> 3); local_10 = local_10 + 1) {
      iVar1 = fprintf(param_1,"%g\r\n",*(undefined8 *)(param_2 + local_10 * 8),iVar1);
    }
    local_5 = 1;
  }
  else {
    local_5 = FUN_004ccae0(param_1,6,param_3,param_2);
  }
  return local_5;
}

