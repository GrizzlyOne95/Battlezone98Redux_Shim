
void __fastcall FUN_0071fcf0(char *param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined1 local_14 [8];
  undefined1 local_c [4];
  char *local_8;
  
  if (*param_1 == '\0') {
    local_8 = param_1;
    cVar1 = FID_conflict_operator__(param_1 + 0x10);
    if ((cVar1 == '\0') &&
       (iVar2 = FUN_006ae390(local_8 + 4),
       (uint)(iVar2 + *(int *)(local_8 + 0x14)) < *(uint *)(local_8 + 0x18))) {
      iVar2 = FUN_006ae390(local_8 + 4);
      *(int *)(local_8 + 0x14) = iVar2 + *(int *)(local_8 + 0x14);
      iVar2 = *(int *)(local_8 + 0x18) - *(int *)(local_8 + 0x14);
      FUN_006f7230(local_c,0);
      uVar3 = get(iVar2);
      puVar4 = (undefined4 *)FUN_006ae430(local_14,uVar3);
      uVar3 = puVar4[1];
      *(undefined4 *)(local_8 + 4) = *puVar4;
      *(undefined4 *)(local_8 + 8) = uVar3;
      return;
    }
    *local_8 = '\x01';
  }
  return;
}

