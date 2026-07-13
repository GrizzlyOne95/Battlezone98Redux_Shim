
undefined4 FUN_0042e770(int param_1,int param_2,int param_3,char param_4)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  undefined1 *puVar6;
  undefined1 *puVar7;
  undefined1 local_58 [12];
  undefined1 local_4c [12];
  undefined1 local_40 [4];
  undefined1 local_3c [4];
  undefined1 local_38 [4];
  undefined1 local_34 [4];
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined4 local_24;
  undefined4 local_20;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined4 local_14;
  undefined4 local_c;
  undefined1 local_6;
  char local_5;
  
  if (param_1 == 0) {
    return 0;
  }
  FUN_004282e0(param_1,0);
  FUN_00428360(&local_c,local_4c);
  uVar2 = FID_conflict_begin(local_28);
  cVar1 = FUN_004221b0(uVar2);
  if (cVar1 != '\0') {
    return 0;
  }
  if (param_2 == 0) {
    puVar7 = local_1c;
    FUN_00422150(puVar7);
    FUN_00420260(puVar7);
    while( true ) {
      puVar7 = local_3c;
      FUN_00422150(puVar7);
      uVar2 = FID_conflict_begin(puVar7);
      cVar1 = FUN_00420f10(uVar2);
      if (cVar1 == '\0') break;
      puVar3 = (undefined4 *)FUN_00422150();
      FUN_0042a910(*puVar3);
      iVar4 = FUN_00422150();
      FUN_0042a910(*(undefined4 *)(iVar4 + 0xc));
      FUN_00428570();
    }
  }
  else {
    FUN_004282e0(param_2,0);
    puVar7 = local_58;
    puVar6 = local_18;
    FUN_00422150(puVar6,puVar7);
    FUN_00428360(puVar6,puVar7);
    puVar7 = local_2c;
    FUN_00422150(puVar7);
    uVar2 = FID_conflict_begin(puVar7);
    cVar1 = FUN_004221b0(uVar2);
    if (cVar1 != '\0') {
      return 0;
    }
    if ((DAT_02cc2b58 & 1) == 0) {
      DAT_02cc2b58 = DAT_02cc2b58 | 1;
      local_6 = 0;
    }
    FUN_00430590();
    local_5 = '\0';
    do {
      puVar3 = (undefined4 *)FUN_004305b0(local_30,0);
      local_14 = *puVar3;
      if (param_3 == 0) {
LAB_0042e8b2:
        puVar3 = (undefined4 *)FUN_00422150();
        FUN_0042a910(*puVar3);
        iVar4 = FUN_00422150();
        FUN_0042a910(*(undefined4 *)(iVar4 + 0xc));
        local_20 = local_14;
        puVar7 = local_34;
        uVar2 = local_14;
        FUN_00422150(puVar7,local_14);
        FUN_00429560(puVar7,uVar2);
        local_5 = '\x01';
      }
      else {
        iVar4 = FUN_00422150();
        cVar1 = FUN_00428890(param_3,*(undefined4 *)(iVar4 + 0xc));
        if (cVar1 == '\0') {
          iVar4 = param_3;
          iVar5 = FUN_00422150(param_3);
          cVar1 = FUN_00428890(*(undefined4 *)(iVar5 + 0xc),iVar4);
          if (cVar1 == '\0') goto LAB_0042e8b2;
        }
      }
      puVar7 = local_38;
      FUN_00422150(puVar7);
      uVar2 = FID_conflict_begin(puVar7);
      cVar1 = FUN_00420f10(uVar2);
      if (cVar1 == '\0') break;
      puVar3 = (undefined4 *)FUN_00422150();
      cVar1 = FUN_004282a0(param_2,*puVar3);
    } while (cVar1 == '\0');
    if (local_5 == '\0') {
      return 0;
    }
    if (param_4 == '\0') {
      return 1;
    }
    FUN_00422150();
    cVar1 = FUN_004202c0();
    if (cVar1 == '\0') {
      return 1;
    }
  }
  puVar3 = (undefined4 *)FUN_00422150();
  FUN_0042a910(*puVar3);
  local_24 = local_c;
  FUN_00428d40(local_40,local_c);
  return 1;
}

