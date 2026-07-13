
void __thiscall FUN_00571e20(undefined4 param_1,undefined2 param_2,uint *param_3,uint param_4)

{
  uint uVar1;
  bool bVar2;
  char cVar3;
  undefined2 uVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  uint local_4c;
  uint local_48;
  int local_40;
  uint local_3c;
  int local_38;
  uint local_34;
  uint local_30;
  uint local_28;
  uint local_24;
  uint local_20;
  uint local_1c;
  uint local_18;
  uint local_14;
  uint local_10;
  uint local_c;
  int local_8;
  
  local_8 = FUN_005771b0(param_2,param_1);
  if (local_8 != 0) {
    if (*param_3 == *(uint *)(local_8 + 0x4c)) {
      uVar6 = FUN_00576040(&local_1c);
      local_30 = FUN_00576160(&local_14);
      local_3c = *param_3;
      if (param_4 < local_3c) {
        local_3c = param_4;
      }
      uVar7 = (param_4 - local_3c >> 1) + local_3c;
      uVar1 = param_3[1];
      if (uVar7 < uVar1) {
        local_38 = uVar1 - uVar7;
      }
      else {
        local_38 = uVar7 - uVar1;
      }
      bVar2 = uVar7 >= uVar1;
      if (param_4 < *param_3) {
        local_40 = 0;
      }
      else {
        local_40 = param_4 - *param_3;
      }
      if (local_3c < uVar1) {
        local_28 = uVar1 - local_3c;
      }
      else {
        local_28 = local_3c - uVar1;
      }
      local_20 = (uint)(local_3c >= uVar1);
      if (param_4 < uVar1) {
        local_24 = uVar1 - param_4;
      }
      else {
        local_24 = param_4 - uVar1;
      }
      local_18 = (uint)(param_4 >= uVar1);
      if (DAT_009180d8 != 0) {
        uVar4 = FUN_0056f920();
        uVar5 = FUN_0081e820("PONG RECEIVED: MST %lu NET DELAY FROM PING = %ld PLAYER %d\n",*param_3
                             ,param_4 - *param_3,uVar4);
        FUN_0081e710(uVar5);
        uVar5 = FUN_0081e820("NEW OFFSET: %lu, %d, %lu\nNEW LOW HIGH: %lu, %lu\nNEWSLOW HIGH: %d, %d\n"
                             ,local_38,bVar2,local_40,local_24,local_28,local_18,local_20);
        FUN_0081e710(uVar5);
      }
      FUN_00576280(local_38,local_40,bVar2,local_24,local_18,local_28,local_20);
      uVar1 = local_1c;
      if (*(char *)(local_8 + 0x8c) != '\0') {
        if ((((local_14 == 0) && (local_20 == 1)) ||
            ((local_14 == 1 && ((local_20 == 1 && (local_30 <= local_28)))))) ||
           ((local_14 == 0 && ((local_20 == 0 && (local_28 <= local_30)))))) {
          local_10 = local_28;
          local_4c = local_20;
          local_c = local_28;
          local_48 = local_20;
        }
        else if ((((local_1c == 1) && (local_18 == 0)) ||
                 ((local_1c == 1 && ((local_18 == 1 && (local_24 <= uVar6)))))) ||
                ((local_1c == 0 && ((local_18 == 0 && (uVar6 <= local_24)))))) {
          local_10 = local_24;
          local_4c = local_18;
          local_c = local_24;
          local_48 = local_18;
        }
        else {
          if ((((local_14 == 0) && (local_1c == 1)) ||
              ((local_14 == 1 && ((local_1c == 1 && (local_30 < uVar6)))))) ||
             ((local_34 = uVar6, local_14 == 0 && ((local_1c == 0 && (uVar6 < local_30)))))) {
            local_1c = local_14;
            local_14 = uVar1;
            local_34 = local_30;
            local_30 = uVar6;
          }
          if ((((local_14 == 0) && (local_18 == 1)) ||
              ((local_14 == 1 && ((local_18 == 1 && (local_30 <= local_24)))))) ||
             ((local_14 == 0 && ((local_18 == 0 && (local_24 <= local_30)))))) {
            local_10 = local_30;
            local_4c = local_14;
          }
          else {
            local_10 = local_24;
            local_4c = local_18;
          }
          if ((((local_1c == 1) && (local_20 == 0)) ||
              ((local_1c == 1 && ((local_20 == 1 && (local_28 <= local_34)))))) ||
             ((local_1c == 0 && ((local_20 == 0 && (local_34 <= local_28)))))) {
            local_c = local_34;
            local_48 = local_1c;
          }
          else {
            local_c = local_28;
            local_48 = local_20;
          }
        }
        if ((local_48 == 1) && (local_4c == 1)) {
          local_38 = (local_10 - local_c >> 1) + local_c;
          bVar2 = true;
          local_40 = local_10 - local_c;
        }
        else if ((local_48 == 0) && (local_4c == 0)) {
          local_38 = (local_c - local_10 >> 1) + local_10;
          bVar2 = false;
          local_40 = local_c - local_10;
        }
        else {
          uVar6 = local_10 + local_c >> 1;
          local_40 = local_10 + local_c;
          if (local_10 < local_c) {
            local_38 = local_c - uVar6;
          }
          else {
            local_38 = local_10 - uVar6;
          }
        }
        if (DAT_009180d8 != 0) {
          uVar5 = FUN_0081e820("HIS LOW HIGH: %lu, %lu\nHISSLOW HIGH: %d, %d\n",local_10,local_c,
                               local_4c,local_48);
          FUN_0081e710(uVar5);
        }
      }
      FUN_00575f20(local_38);
      FUN_00575f40(bVar2);
      FUN_00575f60(local_40);
      *(undefined1 *)(local_8 + 0x8c) = 1;
      if (((*(uint *)(local_8 + 0x1b0) & 1) != 0) && (DAT_009180d8 != 0)) {
        uVar4 = FUN_0056f920();
        uVar5 = FUN_0081e820("Warning, Ping Reply Received after next ping was sent: ping map %X, player %d\n"
                             ,*(undefined4 *)(local_8 + 0x1b0),uVar4);
        FUN_0081e710(uVar5);
      }
      cVar3 = FUN_00577840();
      if ((cVar3 == (char)param_3[2]) || (*(char *)(local_8 + 0x8d) != '\0')) {
        *(undefined1 *)(local_8 + 0x8d) = 1;
        *(uint *)(local_8 + 0x1b0) = *(uint *)(local_8 + 0x1b0) | 1;
      }
      else if (DAT_009180d8 != 0) {
        uVar4 = FUN_0056f920();
        uVar5 = FUN_0081e820("PONG RECEIVED: Treating as lost ping, players heard wrong, player %d\n"
                             ,uVar4);
        FUN_0081e710(uVar5);
        uVar4 = FUN_0056f920();
        FUN_0056fcb0("PONG RECEIVED: Treating as lost ping, players heard wrong, player %d\n",uVar4)
        ;
      }
    }
    else if (DAT_009180d8 != 0) {
      uVar4 = FUN_0056f920();
      uVar5 = FUN_0081e820("PONG RECEIVED: IGNORING MST %lu, EXPECTING %lu, player %d\n",*param_3,
                           *(undefined4 *)(local_8 + 0x4c),uVar4);
      FUN_0081e710(uVar5);
      uVar4 = FUN_0056f920();
      FUN_0056fcb0("PONG RECEIVED: %lu, expecting %lu, player %d\n",*param_3,
                   *(undefined4 *)(local_8 + 0x4c),uVar4);
    }
  }
  return;
}

