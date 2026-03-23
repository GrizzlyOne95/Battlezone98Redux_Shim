
/* WARNING: Removing unreachable block (ram,0x00586d52) */

void FUN_00586c60(uint param_1,uint param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  undefined1 *puVar6;
  undefined1 local_70 [4];
  undefined1 local_6c [4];
  undefined1 local_68 [4];
  undefined1 local_64 [4];
  undefined1 local_60 [4];
  undefined1 local_5c [4];
  undefined4 local_58;
  undefined4 local_54;
  int local_50;
  undefined4 local_4c;
  int *local_48;
  undefined4 *local_40;
  char local_39;
  undefined4 local_38;
  char local_34 [15];
  undefined4 uStack_25;
  undefined1 local_20 [4];
  undefined1 uStack_1c;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849e88;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  param_1 = param_1 & 0x7f7f7f7f;
  param_2 = param_2 & 0x7f7f7f7f;
  if (param_1 != 0 || param_2 != 0) {
    FUN_00422170(local_14);
    puVar2 = (undefined4 *)FID_conflict_begin(local_70);
    local_38 = *puVar2;
    while( true ) {
      uVar3 = FID_conflict_end(local_68);
      cVar1 = FID_conflict_operator__(uVar3);
      if (cVar1 == '\0') break;
      piVar4 = (int *)FUN_00421ec0();
      local_50 = *piVar4;
      if ((*(uint *)(local_50 + 0x18) == param_1) && (*(uint *)(local_50 + 0x1c) == param_2)) {
        FUN_00421ec0();
        goto LAB_00586eaa;
      }
      FUN_0046b260(local_6c,0);
    }
    strncpy((char *)((int)&uStack_25 + 1),(char *)&param_1,8);
    local_4c = 8;
    uStack_1c = 0;
    puVar2 = &uStack_25;
    do {
      local_40 = puVar2;
      local_39 = *(char *)((int)local_40 + 1);
      puVar2 = (undefined4 *)((int)local_40 + 1);
    } while (local_39 != '\0');
    *puVar2 = 0x66646f2e;
    *(undefined1 *)((int)local_40 + 5) = 0;
    local_40 = puVar2;
    iVar5 = FUN_00481f10((int)&uStack_25 + 1);
    if (iVar5 == 0) {
      FUN_007d6c70("Ordnance \"%s\" not found\n",(int)&uStack_25 + 1);
    }
    else {
      FUN_00589430((int)&uStack_25 + 1);
      local_8 = 0;
      FUN_0047b6c0(0xd59a9357,0x92d04727,local_34,0);
      puVar6 = local_64;
      FID_conflict__Immortalize<class_std::_Generic_error_category>(puVar6);
      puVar2 = (undefined4 *)FID_conflict_begin(puVar6);
      local_38 = *puVar2;
      while( true ) {
        puVar6 = local_60;
        FID_conflict__Immortalize<class_std::_Generic_error_category>(puVar6);
        uVar3 = FID_conflict_end(puVar6);
        cVar1 = FID_conflict_operator__(uVar3);
        if (cVar1 == '\0') break;
        local_48 = (int *)FUN_00421ec0();
        local_48 = (int *)*local_48;
        iVar5 = _stricmp((char *)local_48[4],local_34);
        if (iVar5 == 0) {
          local_58 = (**(code **)(*local_48 + 4))(param_1,param_2);
          local_8 = 0xffffffff;
          FUN_00589530();
          goto LAB_00586eaa;
        }
        FUN_0046b260(local_5c,0);
      }
      FUN_007d6c70("Ordnance \"%s\" uses unknown class label \"%s\"\n",(int)&uStack_25 + 1,local_34)
      ;
      local_54 = 0;
      local_8 = 0xffffffff;
      FUN_00589530();
    }
  }
LAB_00586eaa:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

