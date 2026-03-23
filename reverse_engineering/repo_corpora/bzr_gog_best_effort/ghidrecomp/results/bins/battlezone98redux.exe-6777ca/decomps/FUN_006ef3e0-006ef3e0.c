
undefined4 __thiscall
FUN_006ef3e0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,byte param_4)

{
  char *pcVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined4 uVar7;
  int iVar8;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00854cc0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  uVar7 = *param_1;
  pcVar1 = (char *)FUN_004242d0(param_2);
  if (*pcVar1 == '\0') {
    iVar2 = FUN_006fc8d0(param_2,param_4,0,0,0);
    *(undefined4 *)(iVar2 + 4) = param_3;
    puVar3 = (undefined1 *)FUN_00425000(param_2);
    *(undefined1 *)(iVar2 + 0xc) = *puVar3;
    FUN_004242d0(uVar7);
    local_8 = 0;
    puVar4 = (undefined4 *)FUN_00417780(param_2);
    uVar7 = *puVar4;
    uVar5 = FUN_006ef3e0(uVar7,iVar2,param_4);
    puVar4 = (undefined4 *)FUN_00417780(iVar2);
    *puVar4 = uVar5;
    puVar4 = (undefined4 *)FUN_004242f0(param_2);
    uVar6 = (uint)param_4;
    iVar8 = iVar2;
    uVar5 = FUN_006ef3e0(*puVar4,iVar2,uVar6);
    puVar4 = (undefined4 *)FUN_004242f0(iVar2);
    *puVar4 = uVar5;
    uVar7 = FUN_006ef532(iVar8,uVar6,uVar7);
    return uVar7;
  }
  ExceptionList = local_10;
  return uVar7;
}

