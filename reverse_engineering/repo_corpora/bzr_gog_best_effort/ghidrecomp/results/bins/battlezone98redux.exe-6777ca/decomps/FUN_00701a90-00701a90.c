
uint FUN_00701a90(int param_1,uint param_2,undefined4 *param_3)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined1 *puVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined1 local_38 [8];
  undefined1 local_30 [16];
  undefined1 local_20 [8];
  undefined4 local_18;
  int local_14;
  int local_10;
  uint local_c;
  int local_8;
  
  local_c = 0;
  local_10 = 0;
  puVar2 = (undefined4 *)FUN_006ab750();
  uVar6 = puVar2[1];
  *param_3 = *puVar2;
  param_3[1] = uVar6;
  while( true ) {
    while( true ) {
      if (param_2 <= local_c) {
        return local_c;
      }
      if (*(int *)(local_8 + 0x10) != 0) break;
      if (*(char *)(param_1 + local_c) == *(char *)(local_8 + 0xc)) {
        local_c = local_c + 1;
        uVar7 = 1;
        uVar6 = 1;
        puVar5 = local_20;
        FUN_00421ec0(puVar5,1,1);
        local_18 = FUN_006e1b80(puVar5,uVar6,uVar7);
        FID_conflict_operator_(local_18);
        FUN_006ca8c0();
        cVar1 = FUN_006ab7d0();
        if (cVar1 == '\0') {
          puVar2 = (undefined4 *)make_error_code(local_30,8);
          uVar6 = puVar2[1];
          *param_3 = *puVar2;
          param_3[1] = uVar6;
          *(undefined4 *)(local_8 + 0x10) = 3;
        }
        else {
          *(undefined4 *)(local_8 + 0x10) = 1;
        }
      }
      else {
        puVar2 = (undefined4 *)make_error_code(local_38,3);
        uVar6 = puVar2[1];
        *param_3 = *puVar2;
        param_3[1] = uVar6;
        *(undefined4 *)(local_8 + 0x10) = 3;
      }
    }
    if (*(int *)(local_8 + 0x10) != 1) break;
    local_14 = FUN_0070f120(param_1 + local_c,param_1 + param_2,local_8 + 0xd);
    iVar4 = local_14 - (param_1 + local_c);
    iVar3 = param_1 + local_c;
    local_10 = iVar4;
    FUN_00421ec0(iVar3,iVar4);
    FUN_00705220(iVar3,iVar4);
    local_c = local_c + local_10;
    if (local_14 != param_1 + param_2) {
      local_c = local_c + 1;
      *(undefined4 *)(local_8 + 0x10) = 2;
    }
  }
  return local_c;
}

