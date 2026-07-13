
/* WARNING: Removing unreachable block (ram,0x004cce36) */

undefined1 FUN_004ccd80(FILE *param_1,int param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  undefined1 local_14;
  uint local_c;
  undefined1 local_5;
  
  if (DAT_009173b6 == '\0') {
    FUN_004cc410(1,0,0,param_3);
    fprintf(param_1,"%s = ",param_4);
    for (local_c = 0; local_c < param_3; local_c = local_c + 1) {
      fprintf(param_1,"%02x",(uint)*(byte *)(param_2 + local_c));
    }
    iVar1 = putc(0xd,param_1);
    if ((iVar1 == -1) || (iVar1 = putc(10,param_1), iVar1 == -1)) {
      local_14 = 0;
    }
    else {
      local_14 = 1;
    }
    local_5 = local_14;
  }
  else {
    local_5 = FUN_004ccae0(param_1,0,param_3,param_2);
  }
  return local_5;
}

