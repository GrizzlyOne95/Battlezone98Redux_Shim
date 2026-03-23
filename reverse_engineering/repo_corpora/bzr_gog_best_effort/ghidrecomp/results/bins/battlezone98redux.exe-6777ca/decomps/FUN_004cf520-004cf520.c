
undefined1 FUN_004cf520(FILE *param_1,int *param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined1 uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  uint *puVar6;
  bool bVar7;
  undefined8 local_20;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined4 local_10;
  undefined4 local_8;
  
  puVar3 = (undefined4 *)FUN_0046b370(local_14,param_2);
  local_8 = *puVar3;
  uVar4 = FID_conflict_begin(local_18);
  cVar1 = FUN_00420f10(uVar4);
  if (cVar1 == '\0') {
    if (*param_2 == 0) {
      local_20 = 0;
    }
    else {
      puVar6 = (uint *)FUN_004cf950(param_2);
      *puVar6 = DAT_00917a60;
      puVar6[1] = DAT_00917a64;
      local_20 = CONCAT44(DAT_00917a64,DAT_00917a60);
      bVar7 = 0xfffffffe < DAT_00917a60;
      DAT_00917a60 = DAT_00917a60 + 1;
      DAT_00917a64 = DAT_00917a64 + bVar7;
    }
  }
  else {
    iVar5 = FUN_00421ea0();
    local_20 = *(undefined8 *)(iVar5 + 8);
  }
  if (DAT_009173b6 == '\0') {
    FUN_004cc410(1,0,8,param_3);
    local_10 = (undefined4)local_20;
    iVar5 = fprintf(param_1,"%s = %p\r\n",param_4,(undefined4)local_20);
    uVar2 = -1 < iVar5;
  }
  else {
    uVar2 = FUN_004ccae0(param_1,8,8,&local_20);
  }
  return uVar2;
}

