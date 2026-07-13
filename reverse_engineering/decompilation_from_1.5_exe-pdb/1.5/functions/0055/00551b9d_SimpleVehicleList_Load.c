/*
 * Entry: 00551b9d
 * Name: SimpleVehicleList::Load
 * Namespace: SimpleVehicleList
 * Signature: void Load(SimpleVehicleList * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Unable to track spacebase fully for stack */

void __thiscall SimpleVehicleList::Load(SimpleVehicleList *this,char *param_1)

{
  int iVar1;
  void *pvVar2;
  long lVar3;
  char *pcVar4;
  undefined4 auStackY_50 [7];
  undefined4 auStackY_34 [2];
  undefined4 uStackY_2c;
  char *local_c;
  
  if (param_1 != (char *)0x0) {
    pvVar2 = UseItem(param_1);
    uStackY_2c = 0x551bd1;
    lVar3 = GetItemSize(param_1);
    if (pvVar2 != (void *)0x0) {
      iVar1 = -(lVar3 + 1);
      *(long *)(&stack0xffffffdc + iVar1) = lVar3;
      *(void **)(&stack0xffffffd8 + iVar1) = pvVar2;
      *(undefined1 **)((int)&uStackY_2c + iVar1) = &stack0xffffffe0 + iVar1;
      *(undefined4 *)((int)auStackY_34 + iVar1 + 4) = 0x551bf1;
      memcpy();
      (&stack0xffffffe0)[lVar3 + iVar1] = 0;
      *(char **)((int)auStackY_34 + iVar1 + 4) = " \t\r\n";
      *(undefined1 **)((int)auStackY_34 + iVar1) = &stack0xffffffe0 + iVar1;
      *(undefined4 *)((int)auStackY_50 + iVar1 + 0x18) = 0x551c05;
      local_c = strtok(*(char **)((int)auStackY_34 + iVar1),*(char **)((int)auStackY_34 + iVar1 + 4)
                      );
      *(char **)((int)auStackY_50 + iVar1 + 0x18) = " \t\r\n";
      *(undefined4 *)((int)auStackY_50 + iVar1 + 0x14) = 0;
      *(undefined4 *)((int)auStackY_50 + iVar1 + 0x10) = 0x551c0c;
      strtok(*(char **)((int)auStackY_50 + iVar1 + 0x14),*(char **)((int)auStackY_50 + iVar1 + 0x18)
            );
      *(char **)((int)auStackY_50 + iVar1 + 0x10) = " \t\r\n";
      *(undefined4 *)((int)auStackY_50 + iVar1 + 0xc) = 0;
      *(undefined4 *)((int)auStackY_50 + iVar1 + 8) = 0x551c10;
      strtok(*(char **)((int)auStackY_50 + iVar1 + 0xc),*(char **)((int)auStackY_50 + iVar1 + 0x10))
      ;
      *(char **)((int)auStackY_50 + iVar1 + 8) = "\r\n";
      *(undefined4 *)((int)auStackY_50 + iVar1 + 4) = 0;
      *(undefined4 *)((int)auStackY_50 + iVar1) = 0x551c18;
      pcVar4 = strtok(*(char **)((int)auStackY_50 + iVar1 + 4),
                      *(char **)((int)auStackY_50 + iVar1 + 8));
      while ((local_c != (char *)0x0 && (pcVar4 != (char *)0x0))) {
        *(char **)(&stack0xffffffdc + iVar1) = pcVar4;
        *(char **)(&stack0xffffffd8 + iVar1) = local_c;
        *(undefined4 *)((int)&uStackY_2c + iVar1) = 0x551c2d;
        Add(this,*(char **)(&stack0xffffffd8 + iVar1),*(char **)(&stack0xffffffdc + iVar1));
        *(char **)(&stack0xffffffdc + iVar1) = " \t\r\n";
        *(undefined4 *)(&stack0xffffffd8 + iVar1) = 0;
        *(undefined4 *)((int)&uStackY_2c + iVar1) = 0x551c31;
        local_c = strtok(*(char **)(&stack0xffffffd8 + iVar1),*(char **)(&stack0xffffffdc + iVar1));
        *(char **)((int)&uStackY_2c + iVar1) = " \t\r\n";
        *(undefined4 *)((int)auStackY_34 + iVar1 + 4) = 0;
        *(undefined4 *)((int)auStackY_34 + iVar1) = 0x551c38;
        strtok(*(char **)((int)auStackY_34 + iVar1 + 4),*(char **)((int)&uStackY_2c + iVar1));
        *(char **)((int)auStackY_34 + iVar1) = " \t\r\n";
        *(undefined4 *)((int)auStackY_50 + iVar1 + 0x18) = 0;
        *(undefined4 *)((int)auStackY_50 + iVar1 + 0x14) = 0x551c3c;
        strtok(*(char **)((int)auStackY_50 + iVar1 + 0x18),*(char **)((int)auStackY_34 + iVar1));
        *(char **)((int)auStackY_50 + iVar1 + 0x14) = "\r\n";
        *(undefined4 *)((int)auStackY_50 + iVar1 + 0x10) = 0;
        *(undefined4 *)((int)auStackY_50 + iVar1 + 0xc) = 0x551c44;
        pcVar4 = strtok(*(char **)((int)auStackY_50 + iVar1 + 0x10),
                        *(char **)((int)auStackY_50 + iVar1 + 0x14));
      }
      *(char **)(&stack0xffffffdc + iVar1) = param_1;
      *(undefined4 *)(&stack0xffffffd8 + iVar1) = 0x551c54;
      UnlockItem(*(char **)(&stack0xffffffdc + iVar1));
    }
  }
  return;
}
