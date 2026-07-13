
void FUN_006247a0(ushort param_1,char *param_2)

{
  char cVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  char *pcVar6;
  char *local_538;
  char *local_530;
  char *local_52c;
  char *local_528;
  char *local_520;
  short local_518;
  short local_510;
  undefined2 local_508;
  char local_506 [1022];
  char local_108 [256];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00823330(DAT_02a1748c,0);
  FUN_00823390(DAT_02a1748c,0);
  FUN_00821310(DAT_00920168,1,1);
  if (((param_2 != (char *)0x0) && (*param_2 != '\0')) && (iVar3 = FUN_00572a70(), iVar3 != 0)) {
    iVar3 = _stricmp(param_2,"/help");
    if (iVar3 == 0) {
      FUN_00821390(DAT_00920168,"/mute <player> - mute the specified player");
      FUN_007a47b0(0,"/mute <player> - mute the specified player");
      FUN_00821390(DAT_00920168,"/unmute <player> - unmute the specified player");
      FUN_007a47b0(0,"/unmute <player> - unmute the specified player");
      FUN_00821390(DAT_00920168,"/kick <player> - kick out the specified player");
      FUN_007a47b0(0,"/kick <player> - kick out the specified player");
      FUN_00821390(DAT_00920168,"/lock - prevent new players from joining");
      FUN_007a47b0(0,"/lock - prevent new players from joining");
      FUN_00821390(DAT_00920168,"/unlock - allow new players to join");
      FUN_007a47b0(0,"/unlock - allow new players to join");
    }
    else {
      iVar3 = _stricmp(param_2,"/kick");
      if (iVar3 == 0) {
        iVar3 = FUN_00572a60();
        if (iVar3 == 0) {
          uVar4 = FUN_0081cb40("multi_message","only_host_kick");
          FUN_00624710(uVar4);
        }
        else if (param_1 != 0) {
          uVar4 = FUN_005779d0(param_1);
          uVar5 = FUN_0081cb40("multi_message","kicked",uVar4);
          sprintf(local_108,"%s %s",uVar5);
          FUN_00624710(local_108);
          FUN_0081e0c0("Kicked player %s by host slash command\n",uVar4);
          FUN_00572f50(param_1);
        }
      }
      else {
        iVar3 = _stricmp(param_2,"/mute");
        if (iVar3 == 0) {
          if (1 < param_1) {
            uVar4 = FUN_005779d0(param_1);
            uVar5 = FUN_0081cb40("multi_message","muted");
            FUN_00624710(uVar5,uVar4);
            FUN_00572ba0(param_1);
          }
        }
        else {
          iVar3 = _stricmp(param_2,"/unmute");
          if (iVar3 == 0) {
            if ((&DAT_02ceb882)[DAT_0092016c * 0x12] != 0) {
              uVar4 = FUN_005779d0(param_1);
              uVar5 = FUN_0081cb40("multi_message","unmuted");
              FUN_00624710(uVar5,uVar4);
              FUN_00572bd0(param_1);
            }
          }
          else {
            iVar3 = _stricmp(param_2,"/system");
            if ((iVar3 == 0) || (iVar3 = _stricmp(param_2,"/system on"), iVar3 == 0)) {
              uVar4 = FUN_0081cb40("multi_message","system_on");
              FUN_00624710(uVar4);
              DAT_008ec708 = 1;
            }
            else {
              iVar3 = _stricmp(param_2,"/nosystem");
              if ((iVar3 == 0) || (iVar3 = _stricmp(param_2,"/system off"), iVar3 == 0)) {
                uVar4 = FUN_0081cb40("multi_message","system_off");
                FUN_00624710(uVar4);
                DAT_008ec708 = 0;
              }
              else {
                iVar3 = _stricmp(param_2,"/lock");
                if (iVar3 == 0) {
                  iVar3 = FUN_00572a60();
                  if (iVar3 == 0) {
                    uVar4 = FUN_0081cb40("multi_message","only_host_lock");
                    FUN_00624710(uVar4);
                  }
                  else {
                    uVar4 = FUN_0081cb40("multi_message","locked");
                    FUN_00624710(uVar4);
                    FUN_00572e90();
                  }
                }
                else {
                  iVar3 = _stricmp(param_2,"/unlock");
                  if (iVar3 == 0) {
                    iVar3 = FUN_00572a60();
                    if (iVar3 == 0) {
                      uVar4 = FUN_0081cb40("multi_message","only_host_unlock");
                      FUN_00624710(uVar4);
                    }
                    else {
                      uVar4 = FUN_0081cb40("multi_message","unlocked");
                      FUN_00624710(uVar4);
                      FUN_00572ef0();
                    }
                  }
                  else if (*param_2 == '/') {
                    iVar3 = FUN_00573060(param_2 + 1);
                    if (iVar3 == 0) {
                      uVar4 = FUN_0081cb40("multi_message","unknown_command");
                      FUN_00624710(uVar4);
                    }
                  }
                  else {
                    pcVar6 = local_506;
                    sVar2 = FUN_00572d90();
                    if (param_1 == 0xfffa) {
                      iVar3 = FUN_005779d0(sVar2);
                      if (iVar3 != 0) {
                        FUN_00624710("<%s> %s",iVar3,param_2);
                      }
                      local_508 = 0x4350;
                    }
                    else if (param_1 == 0xfff9) {
                      FUN_00624710("<%s> %s",DAT_02cebc98,param_2);
                      local_508 = 0x5370;
                    }
                    else {
                      iVar3 = FUN_005779d0(param_1);
                      if (iVar3 != 0) {
                        FUN_00624710("<%s %s> %s",DAT_02ceb854,iVar3,param_2);
                      }
                      local_508 = 0x5370;
                    }
                    local_538 = param_2;
                    local_530 = pcVar6;
                    do {
                      cVar1 = *local_538;
                      *local_530 = cVar1;
                      local_538 = local_538 + 1;
                      local_530 = local_530 + 1;
                    } while (cVar1 != '\0');
                    if (param_1 == 0xfffa) {
                      for (local_518 = FUN_00577bd0(0,0,0,0); local_518 != 0;
                          local_518 = FUN_00577c90(local_518,0,0,0,0)) {
                        local_528 = param_2;
                        do {
                          cVar1 = *local_528;
                          local_528 = local_528 + 1;
                        } while (cVar1 != '\0');
                        FUN_007659d0(local_518,&local_508,local_528 + (3 - (int)(param_2 + 1)),
                                     pcVar6);
                      }
                    }
                    else if (param_1 == 0xfff9) {
                      for (local_510 = FUN_00577bd0(0,0,0,0); local_510 != 0;
                          local_510 = FUN_00577c90(local_510,0,0,0,0)) {
                        if ((local_510 != sVar2) && (iVar3 = FUN_00577a30(local_510), iVar3 != 0)) {
                          local_520 = param_2;
                          do {
                            cVar1 = *local_520;
                            local_520 = local_520 + 1;
                          } while (cVar1 != '\0');
                          FUN_007659d0(local_510,&local_508,local_520 + (3 - (int)(param_2 + 1)));
                        }
                      }
                    }
                    else {
                      local_52c = param_2;
                      do {
                        cVar1 = *local_52c;
                        local_52c = local_52c + 1;
                      } while (cVar1 != '\0');
                      FUN_007659d0(param_1,&local_508,local_52c + (3 - (int)(param_2 + 1)),pcVar6);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

