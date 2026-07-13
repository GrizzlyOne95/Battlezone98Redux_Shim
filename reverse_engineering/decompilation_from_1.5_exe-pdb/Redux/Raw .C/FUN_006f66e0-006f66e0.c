
void __thiscall FUN_006f66e0(int param_1,uint param_2)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined1 local_20 [8];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined1 local_c [4];
  int local_8;
  
  local_8 = param_1;
  while ((param_2 != 0 && (*(char *)(local_8 + 0xc) == '\0'))) {
    uVar2 = FUN_006ae390(local_8 + 0x10);
    if (param_2 < uVar2) {
      puVar5 = (undefined4 *)FUN_006ae3b0(local_20,local_8 + 0x10,param_2);
      uVar4 = puVar5[1];
      *(undefined4 *)(local_8 + 0x10) = *puVar5;
      *(undefined4 *)(local_8 + 0x14) = uVar4;
      param_2 = 0;
    }
    else {
      iVar3 = FUN_006ae390(local_8 + 0x10);
      param_2 = param_2 - iVar3;
      uVar4 = FID_conflict_end(local_c);
      cVar1 = FID_conflict_operator__(uVar4);
      if (cVar1 == '\0') {
        FUN_006f7230(local_10,0);
        puVar5 = (undefined4 *)get();
        uVar4 = puVar5[1];
        *(undefined4 *)(local_8 + 0x10) = *puVar5;
        *(undefined4 *)(local_8 + 0x14) = uVar4;
      }
      else {
        *(undefined1 *)(local_8 + 0xc) = 1;
      }
    }
  }
  while ((*(char *)(local_8 + 0xc) == '\0' && (iVar3 = FUN_006ae390(local_8 + 0x10), iVar3 == 0))) {
    uVar4 = FID_conflict_end(local_14);
    cVar1 = FID_conflict_operator__(uVar4);
    if (cVar1 == '\0') {
      FUN_006f7230(local_18,0);
      puVar5 = (undefined4 *)get();
      uVar4 = puVar5[1];
      *(undefined4 *)(local_8 + 0x10) = *puVar5;
      *(undefined4 *)(local_8 + 0x14) = uVar4;
    }
    else {
      *(undefined1 *)(local_8 + 0xc) = 1;
    }
  }
  return;
}

