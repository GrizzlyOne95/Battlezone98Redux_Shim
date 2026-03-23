
/* WARNING: Removing unreachable block (ram,0x004ccefe) */

undefined4 FUN_004cce90(FILE *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 extraout_AL;
  undefined3 extraout_var;
  int iVar1;
  undefined3 uVar2;
  undefined1 local_5;
  
  if (DAT_009173b6 == '\0') {
    FUN_004cc410(1,0,2,param_3);
    iVar1 = fprintf(param_1,"%s = %.*s\r\n",param_4,param_3,param_2);
    uVar2 = (undefined3)((uint)iVar1 >> 8);
    local_5 = 1;
  }
  else {
    FUN_004ccae0(param_1,2,param_3,param_2);
    uVar2 = extraout_var;
    local_5 = extraout_AL;
  }
  return CONCAT31(uVar2,local_5);
}

