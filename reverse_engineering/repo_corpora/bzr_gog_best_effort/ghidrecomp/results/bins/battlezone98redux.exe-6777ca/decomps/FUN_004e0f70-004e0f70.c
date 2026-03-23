
void FUN_004e0f70(uint param_1,uint param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  undefined1 *puVar6;
  undefined1 local_68 [4];
  undefined1 local_64 [4];
  undefined1 local_60 [4];
  undefined1 local_5c [4];
  undefined1 local_58 [4];
  undefined1 local_54 [4];
  undefined4 local_50;
  undefined4 local_4c;
  int local_48;
  int local_44;
  int *local_3c;
  undefined4 local_38;
  char local_34 [16];
  char local_24 [16];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a248;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  param_1 = param_1 & 0x7f7f7f7f;
  param_2 = param_2 & 0x7f7f7f7f;
  if (param_1 != 0 || param_2 != 0) {
    FUN_00422170(local_14);
    puVar2 = (undefined4 *)FID_conflict_begin(local_54);
    local_38 = *puVar2;
    while( true ) {
      uVar3 = FID_conflict_end(local_68);
      cVar1 = FID_conflict_operator__(uVar3);
      if (cVar1 == '\0') break;
      piVar4 = (int *)FUN_00421ec0();
      local_48 = *piVar4;
      local_44 = local_48;
      if ((*(uint *)(local_48 + 0x30) == param_1) && (*(uint *)(local_48 + 0x34) == param_2))
      goto LAB_004e1175;
      FUN_0046b260(local_60,0);
    }
    sprintf(local_24,"%.8s.odf",&param_1);
    iVar5 = FUN_00481f10(local_24);
    if (iVar5 == 0) {
      FUN_007d6c70("GameObject \"%s\" not found\n",local_24);
    }
    else {
      FUN_00589430(local_24);
      local_8 = 0;
      FUN_0047b6c0(0xd3dd9cec,0x92d04727,local_34,0);
      puVar6 = local_5c;
      FID_conflict__Immortalize<class_std::_Generic_error_category>(puVar6);
      puVar2 = (undefined4 *)FID_conflict_begin(puVar6);
      local_38 = *puVar2;
      while( true ) {
        puVar6 = local_58;
        FID_conflict__Immortalize<class_std::_Generic_error_category>(puVar6);
        uVar3 = FID_conflict_end(puVar6);
        cVar1 = FID_conflict_operator__(uVar3);
        if (cVar1 == '\0') break;
        local_3c = (int *)FUN_00421ec0();
        local_3c = (int *)*local_3c;
        if ((local_3c[6] != 0) && (iVar5 = _stricmp((char *)local_3c[6],local_34), iVar5 == 0)) {
          local_50 = (**(code **)(*local_3c + 8))(param_1,param_2);
          local_8 = 0xffffffff;
          FUN_00589530();
          goto LAB_004e1175;
        }
        FUN_0046b260(local_64,0);
      }
      FUN_007d6c70("GameObject \"%s\" uses unknown class label \"%s\"\n",local_24,local_34);
      local_4c = 0;
      local_8 = 0xffffffff;
      FUN_00589530();
    }
  }
LAB_004e1175:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

