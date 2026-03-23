
undefined4 FUN_00426cf0(int param_1,int param_2,undefined4 param_3,undefined1 *param_4)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined1 *puVar5;
  undefined1 local_38 [12];
  undefined1 local_2c [12];
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  undefined1 local_8 [4];
  
  if (param_4 != (undefined1 *)0x0) {
    *param_4 = 0;
  }
  if ((param_1 != 0) && (param_2 != 0)) {
    FUN_004282e0(param_1,0);
    FUN_00428400(local_8,local_2c);
    uVar2 = FID_conflict_begin(local_18);
    cVar1 = FUN_004221b0(uVar2);
    if (cVar1 == '\0') {
      FUN_004282e0(param_2,0);
      puVar5 = local_38;
      puVar3 = &local_10;
      FUN_00421ea0(puVar3,puVar5);
      FUN_00428400(puVar3,puVar5);
      puVar5 = local_1c;
      FUN_00421ea0(puVar5);
      uVar2 = FID_conflict_begin(puVar5);
      cVar1 = FUN_004221b0(uVar2);
      if (cVar1 == '\0') {
        if ((*(char *)(local_c + 0x1d) != '\0') && (param_4 != (undefined1 *)0x0)) {
          local_14 = local_10;
          puVar5 = local_20;
          FUN_00421ea0(puVar5);
          uVar2 = FID_conflict_begin(puVar5);
          FUN_00422190(uVar2);
          cVar1 = FUN_00420f10(uVar2);
          if (cVar1 != '\0') {
            puVar3 = (undefined4 *)FUN_00421ea0();
            cVar1 = FUN_004282a0(param_2,*puVar3);
            if (cVar1 == '\0') {
              *param_4 = 1;
            }
          }
        }
        iVar4 = FUN_00421ea0();
        param_3 = *(undefined4 *)(iVar4 + 0xc);
      }
    }
  }
  return param_3;
}

