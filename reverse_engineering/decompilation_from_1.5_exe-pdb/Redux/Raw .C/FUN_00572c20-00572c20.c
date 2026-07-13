
/* WARNING: Function: __alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

void FUN_00572c20(void)

{
  code *pcVar1;
  int iVar2;
  char *pcVar3;
  undefined4 auStack_6c [3];
  int iStack_60;
  char *pcStack_5c;
  undefined1 *local_58;
  undefined1 *local_54;
  undefined1 *local_50;
  char *local_4c;
  char *local_48;
  int *local_44;
  undefined1 *local_40;
  int local_3c;
  char *local_38;
  int *local_34;
  undefined1 *local_30;
  char *local_2c;
  char *local_28;
  undefined1 local_22;
  char local_21;
  undefined1 local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  pcStack_5c = (char *)0x572c35;
  FUN_00764760();
  pcStack_5c = (char *)0x572c3c;
  local_3c = FUN_0056f900();
  if (local_3c != 0) {
    pcStack_5c = "gameended";
    iStack_60 = 0x572c59;
    basic_string<>();
    pcStack_5c = (char *)0x572c5e;
    local_44 = (int *)FUN_00764760();
    pcStack_5c = local_20;
    iStack_60 = local_3c + 0x10;
    auStack_6c[2] = 0x572c79;
    local_48 = (char *)(**(code **)(*local_44 + 0x2c))();
    auStack_6c[2] = 0x572c84;
    ~basic_string<>();
    if ((local_48 == (char *)0x0) || (*local_48 != '1')) {
      local_28 = &DAT_00917f58;
      local_50 = &DAT_00917f59;
      pcVar3 = local_28;
      do {
        local_28 = pcVar3;
        pcVar3 = local_28 + 1;
      } while (*local_28 != '\0');
      local_4c = local_28 + -0x917f58;
      auStack_6c[2] = 0x572cd2;
      iVar2 = -(int)(local_28 + -0x917f57);
      local_58 = (undefined1 *)((int)&iStack_60 + iVar2);
      local_54 = (undefined1 *)((int)&iStack_60 + iVar2);
      local_30 = (undefined1 *)((int)&iStack_60 + iVar2);
      local_2c = (char *)((int)&iStack_60 + iVar2);
      local_38 = &DAT_00917f58;
      local_22 = 0;
      local_28 = local_28 + 1;
      do {
        local_21 = *local_38;
        *local_2c = local_21;
        local_38 = local_38 + 1;
        local_2c = local_2c + 1;
      } while (local_21 != '\0');
      *(undefined4 *)((int)auStack_6c + iVar2 + 8) = 0x2e;
      *(undefined1 **)((int)auStack_6c + iVar2 + 4) = local_30;
      *(undefined4 *)((int)auStack_6c + iVar2) = 0x572d21;
      local_40 = (undefined1 *)FUN_00434140();
      if (local_40 != (undefined1 *)0x0) {
        *local_40 = 0;
      }
      *(undefined4 *)((int)auStack_6c + iVar2 + 8) = 0x572d38;
      local_34 = (int *)FUN_0045ca50();
      if (local_34 == (int *)0x0) {
        *(undefined1 **)((int)auStack_6c + iVar2 + 8) = local_30;
        *(undefined4 *)((int)auStack_6c + iVar2 + 4) = 0x572d59;
        FUN_0045c990();
      }
      else {
        pcVar1 = *(code **)(*local_34 + 0x3c);
        *(undefined4 *)((int)auStack_6c + iVar2 + 8) = 0x572d4e;
        (*pcVar1)();
      }
    }
  }
  pcStack_5c = (char *)0x572d6e;
  FUN_0083e885();
  return;
}

