
undefined4 FUN_004ccd10(FILE *param_1,undefined4 param_2)

{
  uint uVar1;
  int iVar2;
  bool local_5;
  
  uVar1 = (uint)DAT_009173b6;
  if (uVar1 == 0) {
    FUN_004cc410(1,0,0xff,0);
    iVar2 = fprintf(param_1,"%s\r\n",param_2);
    local_5 = 0 < iVar2;
    uVar1 = CONCAT31((int3)((uint)iVar2 >> 8),local_5);
  }
  else {
    local_5 = true;
  }
  return CONCAT31((int3)(uVar1 >> 8),local_5);
}

