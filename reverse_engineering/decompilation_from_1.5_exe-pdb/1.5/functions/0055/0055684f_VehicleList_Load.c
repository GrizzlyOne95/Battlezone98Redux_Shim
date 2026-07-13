/*
 * Entry: 0055684f
 * Name: VehicleList::Load
 * Namespace: VehicleList
 * Signature: void Load(VehicleList * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Unable to track spacebase fully for stack */

void __thiscall VehicleList::Load(VehicleList *this,char *param_1)

{
  char cVar1;
  byte bVar2;
  void *pvVar3;
  long lVar4;
  char *pcVar5;
  byte *pbVar6;
  int iVar7;
  byte *pbVar8;
  int iVar9;
  _s *p_Var10;
  bool bVar11;
  undefined4 auStackY_6c [7];
  undefined4 uStackY_50;
  char *local_2c;
  char *local_28;
  char *local_24;
  char *local_20;
  byte local_1c [20];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (param_1 != (char *)0x0) {
    pvVar3 = UseItem(param_1);
    uStackY_50 = 0x556884;
    lVar4 = GetItemSize(param_1);
    if (pvVar3 != (void *)0x0) {
      iVar9 = -(lVar4 + 1);
      *(long *)(&stack0xffffffb8 + iVar9) = lVar4;
      *(void **)(&stack0xffffffb4 + iVar9) = pvVar3;
      *(undefined1 **)((int)&uStackY_50 + iVar9) = &stack0xffffffbc;
      *(undefined4 *)((int)auStackY_6c + iVar9 + 0x18) = 0x5568a6;
      memcpy();
      (&stack0xffffffbc)[lVar4] = 0;
      if (this->count == 0) {
        pcVar5 = net_defaults.playercraft;
      }
      else {
        *(undefined4 *)(&stack0xffffffb8 + iVar9) = 0x5568ba;
        pcVar5 = GetName(this);
      }
      if (pcVar5 == (char *)0x0) {
        local_1c[0] = 0;
      }
      else {
        iVar7 = -(int)pcVar5;
        do {
          cVar1 = *pcVar5;
          pcVar5[(int)(local_1c + iVar7)] = cVar1;
          pcVar5 = pcVar5 + 1;
        } while (cVar1 != '\0');
      }
      *(undefined4 *)(&stack0xffffffb8 + iVar9) = 0x5568e1;
      Init(this);
      *(char **)(&stack0xffffffb8 + iVar9) = " \t\r\n";
      *(undefined1 **)(&stack0xffffffb4 + iVar9) = &stack0xffffffbc;
      *(undefined4 *)((int)&uStackY_50 + iVar9) = 0x5568f0;
      local_2c = strtok(*(char **)(&stack0xffffffb4 + iVar9),*(char **)(&stack0xffffffb8 + iVar9));
      *(char **)((int)&uStackY_50 + iVar9) = " \t\r\n";
      *(undefined4 *)((int)auStackY_6c + iVar9 + 0x18) = 0;
      *(undefined4 *)((int)auStackY_6c + iVar9 + 0x14) = 0x5568f8;
      local_28 = strtok(*(char **)((int)auStackY_6c + iVar9 + 0x18),
                        *(char **)((int)&uStackY_50 + iVar9));
      *(char **)((int)auStackY_6c + iVar9 + 0x14) = " \t\r\n";
      *(undefined4 *)((int)auStackY_6c + iVar9 + 0x10) = 0;
      *(undefined4 *)((int)auStackY_6c + iVar9 + 0xc) = 0x556900;
      local_20 = strtok(*(char **)((int)auStackY_6c + iVar9 + 0x10),
                        *(char **)((int)auStackY_6c + iVar9 + 0x14));
      *(char **)((int)auStackY_6c + iVar9 + 0xc) = "\r\n";
      *(undefined4 *)((int)auStackY_6c + iVar9 + 8) = 0;
      *(undefined4 *)((int)auStackY_6c + iVar9 + 4) = 0x55690d;
      local_24 = strtok(*(char **)((int)auStackY_6c + iVar9 + 8),
                        *(char **)((int)auStackY_6c + iVar9 + 0xc));
      while ((((local_2c != (char *)0x0 && (local_28 != (char *)0x0)) && (local_20 != (char *)0x0))
             && (local_24 != (char *)0x0))) {
        while( true ) {
          *(int *)(&stack0xffffffb8 + iVar9) = (int)*local_24;
          *(undefined4 *)(&stack0xffffffb4 + iVar9) = 0x556946;
          iVar7 = isspace(*(int *)(&stack0xffffffb8 + iVar9));
          if (iVar7 == 0) break;
          local_24 = local_24 + 1;
        }
        *(char **)(&stack0xffffffb8 + iVar9) = local_28;
        *(undefined4 *)(&stack0xffffffb4 + iVar9) = 0x556953;
        lVar4 = GetItemSize(*(char **)(&stack0xffffffb8 + iVar9));
        *(char **)(&stack0xffffffb4 + iVar9) = local_28;
        *(undefined4 *)((int)&uStackY_50 + iVar9) = 0x55695e;
        pvVar3 = UseItem(*(char **)(&stack0xffffffb4 + iVar9));
        if ((lVar4 < 1) || (pvVar3 == (void *)0x0)) {
          *(char **)(&stack0xffffffb8 + iVar9) = local_24;
          *(char **)(&stack0xffffffb4 + iVar9) = local_20;
          *(char **)((int)&uStackY_50 + iVar9) = local_28;
        }
        else {
          *(char **)(&stack0xffffffb8 + iVar9) = local_24;
          *(char **)(&stack0xffffffb4 + iVar9) = local_20;
          *(void **)((int)&uStackY_50 + iVar9) = pvVar3;
        }
        *(char **)((int)auStackY_6c + iVar9 + 0x18) = local_2c;
        *(undefined4 *)((int)auStackY_6c + iVar9 + 0x14) = 0x556987;
        Add(this,*(char **)((int)auStackY_6c + iVar9 + 0x18),*(char **)((int)&uStackY_50 + iVar9),
            *(char **)(&stack0xffffffb4 + iVar9),*(char **)(&stack0xffffffb8 + iVar9));
        *(char **)(&stack0xffffffb8 + iVar9) = local_28;
        *(undefined4 *)(&stack0xffffffb4 + iVar9) = 0x55698f;
        UnlockItem(*(char **)(&stack0xffffffb8 + iVar9));
        *(char **)(&stack0xffffffb4 + iVar9) = " \t\r\n";
        *(undefined4 *)((int)&uStackY_50 + iVar9) = 0;
        *(undefined4 *)((int)auStackY_6c + iVar9 + 0x18) = 0x556994;
        local_2c = strtok(*(char **)((int)&uStackY_50 + iVar9),*(char **)(&stack0xffffffb4 + iVar9))
        ;
        *(char **)((int)auStackY_6c + iVar9 + 0x18) = " \t\r\n";
        *(undefined4 *)((int)auStackY_6c + iVar9 + 0x14) = 0;
        *(undefined4 *)((int)auStackY_6c + iVar9 + 0x10) = 0x55699c;
        local_28 = strtok(*(char **)((int)auStackY_6c + iVar9 + 0x14),
                          *(char **)((int)auStackY_6c + iVar9 + 0x18));
        *(char **)((int)auStackY_6c + iVar9 + 0x10) = " \t\r\n";
        *(undefined4 *)((int)auStackY_6c + iVar9 + 0xc) = 0;
        *(undefined4 *)((int)auStackY_6c + iVar9 + 8) = 0x5569a4;
        local_20 = strtok(*(char **)((int)auStackY_6c + iVar9 + 0xc),
                          *(char **)((int)auStackY_6c + iVar9 + 0x10));
        *(char **)((int)auStackY_6c + iVar9 + 8) = "\r\n";
        *(undefined4 *)((int)auStackY_6c + iVar9 + 4) = 0;
        *(undefined4 *)((int)auStackY_6c + iVar9) = 0x5569ac;
        local_24 = strtok(*(char **)((int)auStackY_6c + iVar9 + 4),
                          *(char **)((int)auStackY_6c + iVar9 + 8));
      }
      *(char **)(&stack0xffffffb8 + iVar9) = param_1;
      *(undefined4 *)(&stack0xffffffb4 + iVar9) = 0x5569c4;
      UnlockItem(*(char **)(&stack0xffffffb8 + iVar9));
    }
  }
  iVar9 = 0;
  this->currentSelection = 0;
  if (0 < this->count) {
    p_Var10 = this->s;
    do {
      pbVar6 = (byte *)p_Var10->name;
      pbVar8 = local_1c;
      do {
        bVar2 = *pbVar6;
        bVar11 = bVar2 < *pbVar8;
        if (bVar2 != *pbVar8) {
LAB_005569f8:
          iVar7 = (1 - (uint)bVar11) - (uint)(bVar11 != 0);
          goto LAB_005569fd;
        }
        if (bVar2 == 0) break;
        bVar2 = pbVar6[1];
        bVar11 = bVar2 < pbVar8[1];
        if (bVar2 != pbVar8[1]) goto LAB_005569f8;
        pbVar6 = pbVar6 + 2;
        pbVar8 = pbVar8 + 2;
      } while (bVar2 != 0);
      iVar7 = 0;
LAB_005569fd:
      if (iVar7 == 0) {
        this->currentSelection = iVar9;
        break;
      }
      iVar9 = iVar9 + 1;
      p_Var10 = p_Var10 + 1;
    } while (iVar9 < this->count);
  }
  SetCurrentSelection(this);
  return;
}
