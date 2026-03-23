
void FUN_0044e4c0(char *param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_16c [4];
  undefined4 local_168;
  undefined4 local_164;
  undefined1 local_15c [4];
  int *local_158;
  undefined1 local_154 [64];
  undefined1 local_114 [64];
  char local_d4 [128];
  char local_54 [64];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008468eb;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  local_168 = FUN_00446460(param_1,0x811c9dc5,uVar2);
  FUN_0044eb20(local_15c,&local_168);
  uVar3 = FUN_0044eaa0(local_16c);
  cVar1 = FUN_00420f10(uVar3);
  if (cVar1 == '\0') {
    iVar4 = _stricmp(param_1,"NULL");
    if (iVar4 != 0) {
      FUN_00588c30(param_1,local_114,local_154,0x40,0x40);
      sprintf(local_54,"%.*s.odf",0x3b,local_114);
      local_158 = (int *)0x0;
      iVar4 = FUN_00481f10(local_54);
      if (iVar4 == 0) {
        FUN_007d6c70("ERROR: Effect \"%s\" does not exist\n",local_54);
        local_158 = (int *)0x0;
      }
      else {
        FUN_00589430(local_54);
        local_8 = 0;
        uVar3 = FUN_00446460(local_54,0x811c9dc5);
        local_164 = FUN_00446460(local_154,0x811c9dc5,uVar2,uVar3);
        FUN_0044fb50(local_164,0x89460500,local_d4,0);
        if (local_d4[0] == '\0') {
          FUN_007d6c70("ERROR: Effect \"%s\" has no base class specified",param_1);
        }
        else {
          local_158 = (int *)FUN_0044e4c0(local_d4);
          if (local_158 == (int *)0x0) {
            FUN_007d6c70("ERROR: Effect \"%s\" cannot find base class \"%s\"",param_1,local_d4);
          }
          else {
            local_158 = (int *)(**(code **)(*local_158 + 0xc))(param_1);
          }
        }
        local_8 = 0xffffffff;
        FUN_00589530();
      }
    }
  }
  else {
    FUN_0042da60();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

