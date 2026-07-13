/*
 * Entry: 004b2127
 * Name: load_textable
 * Namespace: Global
 * Signature: void load_textable(char * param_1, textab * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl load_textable(char *param_1,textab *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  void *pvVar3;
  int *piVar4;
  int iVar5;
  int unaff_EBX;
  undefined4 *puVar6;
  int local_10;
  int local_c;
  void *local_8;
  
  local_8 = UseItem(param_1);
  if (local_8 != (void *)0x0) {
    *(undefined4 *)(unaff_EBX + 0x14) = *(undefined4 *)((int)local_8 + 0x28);
    *(undefined4 *)(unaff_EBX + 0x18) = *(undefined4 *)((int)local_8 + 0x2c);
    *(undefined4 *)(unaff_EBX + 0x1c) = *(undefined4 *)((int)local_8 + 0x14);
    iVar2 = *(int *)((int)local_8 + 0x14);
    local_10 = 1;
    iVar5 = 0;
    if (0 < iVar2) {
      piVar4 = (int *)(unaff_EBX + 0x20);
      do {
        local_10 = *(int *)((int)local_8 + (iVar2 - iVar5) * 4 + 0x14) * local_10;
        *piVar4 = local_10;
        iVar2 = *(int *)((int)local_8 + 0x14);
        iVar5 = iVar5 + 1;
        piVar4 = piVar4 + 1;
      } while (iVar5 < iVar2);
    }
    pvVar3 = operator_new__(local_10 << 4);
    *(void **)(unaff_EBX + 0x2c) = pvVar3;
    if (0 < local_10) {
      local_c = 0;
      local_8 = (void *)((int)local_8 + 0x40);
      do {
        pvVar3 = (void *)(*(int *)(unaff_EBX + 0x2c) + local_c);
        memmove(pvVar3,local_8,8);
        *(undefined1 *)((int)pvVar3 + 8) = 0;
        puVar1 = (undefined4 *)((int)pvVar3 + -1);
        do {
          puVar6 = puVar1;
          puVar1 = (undefined4 *)((int)puVar6 + 1);
        } while (*(char *)((int)puVar6 + 1) != '\0');
        local_8 = (void *)((int)local_8 + 8);
        local_c = local_c + 0x10;
        local_10 = local_10 + -1;
        *(undefined4 *)((int)puVar6 + 1) = 0x70616d2e;
        *(undefined1 *)((int)puVar6 + 5) = 0;
      } while (local_10 != 0);
    }
    *(undefined4 *)(unaff_EBX + 0x10) = 0;
    UnlockItem(param_1);
  }
  return;
}
