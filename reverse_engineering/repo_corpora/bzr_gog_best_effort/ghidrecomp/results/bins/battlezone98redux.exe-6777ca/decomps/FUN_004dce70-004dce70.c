
void FUN_004dce70(undefined4 param_1,int *param_2)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int *local_b8;
  int local_b4;
  undefined4 local_b0;
  uint local_ac;
  int local_a8;
  undefined4 local_a4;
  uint local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  char *local_90;
  char *local_8c;
  char *local_88;
  short local_84 [3];
  undefined1 local_7e;
  char local_7d;
  undefined4 local_7c [16];
  undefined1 local_3c [12];
  char local_30 [40];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar2 = (**(code **)(param_2[6] + 0x30))();
  local_98 = *(undefined4 *)(iVar2 + 8);
  local_94 = *(undefined4 *)(iVar2 + 0xc);
  local_84[0] = FUN_00462450();
  FUN_004c0af0(local_3c);
  local_b0 = (**(code **)(param_2[6] + 4))();
  piVar3 = (int *)FUN_00417c70();
  local_a0 = (uint)(param_2 == piVar3);
  local_ac = local_a0;
  puVar4 = (undefined4 *)FUN_0045c4d0();
  puVar5 = local_7c;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar5 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
  }
  local_b8 = param_2;
  local_a8 = (**(code **)param_2[6])();
  local_b4 = FUN_004e0f70(local_98,local_94);
  local_90 = (char *)FUN_004623e0();
  local_30[0] = '\0';
  local_30[1] = '\0';
  local_30[2] = '\0';
  local_30[3] = '\0';
  local_30[4] = '\0';
  local_30[5] = '\0';
  local_30[6] = '\0';
  local_30[7] = '\0';
  local_30[8] = '\0';
  local_30[9] = '\0';
  local_30[10] = '\0';
  local_30[0xb] = '\0';
  local_30[0xc] = '\0';
  local_30[0xd] = '\0';
  local_30[0xe] = '\0';
  local_30[0xf] = '\0';
  local_30[0x10] = '\0';
  local_30[0x11] = '\0';
  local_30[0x12] = '\0';
  local_30[0x13] = '\0';
  local_30[0x14] = '\0';
  local_30[0x15] = '\0';
  local_30[0x16] = '\0';
  local_30[0x17] = '\0';
  local_30[0x18] = '\0';
  local_30[0x19] = '\0';
  local_30[0x1a] = '\0';
  local_30[0x1b] = '\0';
  local_30[0x1c] = '\0';
  local_30[0x1d] = '\0';
  local_30[0x1e] = '\0';
  local_30[0x1f] = '\0';
  local_30[0x20] = '\0';
  local_30[0x21] = '\0';
  local_30[0x22] = '\0';
  local_30[0x23] = '\0';
  local_30[0x24] = '\0';
  local_30[0x25] = '\0';
  local_30[0x26] = '\0';
  local_30[0x27] = '\0';
  if (local_90 == (char *)0x0) {
    sprintf(local_30,"%.8s%d_%s",&local_98,(int)local_84[0],*(undefined4 *)(local_a8 + 0x18));
  }
  else {
    local_88 = local_30;
    local_8c = local_90;
    do {
      cVar1 = *local_8c;
      *local_88 = cVar1;
      local_8c = local_8c + 1;
      local_88 = local_88 + 1;
    } while (cVar1 != '\0');
    local_7e = 0;
  }
  cVar1 = FUN_004ccd10(param_1,"[GameObject]");
  if ((((((cVar1 == '\0') || (cVar1 = FUN_004cda70(param_1,&local_98,8,"PrjID"), cVar1 == '\0')) ||
        (cVar1 = FUN_004cd0e0(param_1,local_84,2,"seqno"), cVar1 == '\0')) ||
       ((cVar1 = FUN_004cd520(param_1,local_3c,0xc,&DAT_00875e34), cVar1 == '\0' ||
        (cVar1 = FUN_004cd1b0(param_1,&local_b0,4,&DAT_008757b0), cVar1 == '\0')))) ||
      ((cVar1 = FUN_004cce90(param_1,local_30,0x28,"label"), cVar1 == '\0' ||
       ((cVar1 = FUN_004cd1b0(param_1,&local_ac,4,"isUser"), cVar1 == '\0' ||
        (cVar1 = FUN_004cf520(param_1,&local_b8,4,"obj_addr"), cVar1 == '\0')))))) ||
     (cVar1 = FUN_004cd790(param_1,local_7c,0x40,"transform"), cVar1 == '\0')) {
    local_9c = 0;
  }
  else {
    local_9c = 1;
  }
  local_7d = (char)local_9c;
  if (local_b4 != 0) {
    if (((char)local_9c == '\0') || (cVar1 = (**(code **)(*param_2 + 0x54))(param_1), cVar1 == '\0')
       ) {
      local_a4 = 0;
    }
    else {
      local_a4 = 1;
    }
    local_7d = (char)local_a4;
  }
  FUN_0083e885();
  return;
}

