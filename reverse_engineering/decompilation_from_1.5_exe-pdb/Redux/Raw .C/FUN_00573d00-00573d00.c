
undefined4
FUN_00573d00(char param_1,char param_2,char param_3,uint param_4,uint param_5,int param_6,
            int param_7,undefined4 *param_8)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 local_8;
  
  local_8 = 0;
  if (param_8 == (undefined4 *)0x0) {
    param_8 = &local_8;
  }
  *param_8 = 0;
  if (DAT_00917f48 == 0) {
    cVar1 = FUN_0041f890();
    if (cVar1 == '\0') {
      if ((*(short *)(param_7 + 0x10) == 0) || (*(int *)(param_7 + 0x2c) < 1)) {
        FUN_00573cc0("CanLaunchGame: NotAvailable - User\'s small ID or team not set\n");
        uVar2 = FUN_0081cb40("launch_issue","team_unset");
        *param_8 = uVar2;
        uVar2 = 0;
      }
      else {
        cVar1 = FUN_0041f890();
        if (cVar1 == '\0') {
          cVar1 = FUN_0041f890();
          if (cVar1 == '\0') {
            if (((*(char *)(param_6 + 0x30) == '\0') || (*(char *)(param_7 + 0x60) == '\0')) ||
               (*(int *)(param_7 + 100) != *(int *)(param_6 + 0x34))) {
              FUN_00573cc0("CanLaunchGame: NotAvailable - Map CRC Mismatch\n");
              uVar2 = FUN_0081cb40("multi_two","map_crc_fail");
              *param_8 = uVar2;
              uVar2 = 0;
            }
            else if (*(int *)(param_6 + 0x58) == 0) {
              FUN_00573cc0("CanLaunchGame: NotAvailable - Lives not set\n");
              uVar2 = FUN_0081cb40("launch_issue","setting_lives_unset");
              *param_8 = uVar2;
              uVar2 = 0;
            }
            else {
              if (param_1 == '\0') {
                if ((param_2 != '\0') && (param_3 != '\0')) {
                  FUN_00573cc0("CanLaunchGame: CanLaunchOrNotReady\n");
                  return 4;
                }
              }
              else {
                if ((*(char *)(param_6 + 0x50) != '\0') && ((int)param_4 < 1)) {
                  if (param_3 != '\0') {
                    FUN_00573cc0("CanLaunchGame: NotReady - Not enough client\'s to sync launch\n");
                    uVar2 = FUN_0081cb40("launch_issue","sync_need_min");
                    *param_8 = uVar2;
                    return 1;
                  }
                  FUN_00573cc0("CanLaunchGame: CanReady - Not enough client\'s to sync launch\n");
                  return 2;
                }
                if ((*(char *)(param_6 + 0x50) == '\0') && (param_4 < *(uint *)(param_6 + 0x5c))) {
                  if (param_3 != '\0') {
                    FUN_00573cc0("CanLaunchGame: CanLaunchOrNotReady - NonSync\n");
                    return 4;
                  }
                  FUN_00573cc0("CanLaunchGame: CanShowLaunch - NonSync\n");
                  return 3;
                }
                if (((param_3 != '\0') && (param_4 == param_5)) &&
                   (param_4 < *(uint *)(param_6 + 0x5c))) {
                  FUN_00573cc0("CanLaunchGame: CanLaunchOrNotReady\n");
                  return 4;
                }
                if (((param_3 == '\0') && (param_4 == param_5)) &&
                   (param_4 < *(uint *)(param_6 + 0x5c))) {
                  FUN_00573cc0("CanLaunchGame: CanShowLaunch\n");
                  return 3;
                }
              }
              if (param_3 == '\0') {
                if (param_4 < *(uint *)(param_6 + 0x5c)) {
                  FUN_00573cc0("CanLaunchGame: CanReady\n");
                  uVar2 = 2;
                }
                else {
                  FUN_00573cc0("CanLaunchGame: NotAvailable - Too many players?\n");
                  uVar2 = FUN_0081cb40("launch_issue","game_full");
                  *param_8 = uVar2;
                  uVar2 = 0;
                }
              }
              else {
                FUN_00573cc0("CanLaunchGame: NotReady\n");
                if (param_1 != '\0') {
                  uVar2 = FUN_0081cb40("launch_issue","player_not_ready");
                  *param_8 = uVar2;
                }
                uVar2 = 1;
              }
            }
          }
          else {
            FUN_00573cc0("CanLaunchGame: NotAvailable - User\'s vehicle not set\n");
            uVar2 = FUN_0081cb40("launch_issue","setting_vehicle_unset");
            *param_8 = uVar2;
            uVar2 = 0;
          }
        }
        else {
          FUN_00573cc0("CanLaunchGame: NotAvailable - Map not set\n");
          uVar2 = FUN_0081cb40("launch_issue","setting_map_unset");
          *param_8 = uVar2;
          uVar2 = 0;
        }
      }
    }
    else {
      FUN_00573cc0("CanLaunchGame: NotAvailable - Game not named\n");
      uVar2 = FUN_0081cb40("launch_issue","name_empty");
      *param_8 = uVar2;
      uVar2 = 0;
    }
  }
  else {
    FUN_00573cc0("CanLaunchGame: NotAvailable - Game already running\n");
    uVar2 = FUN_0081cb40("launch_issue","game_launching");
    *param_8 = uVar2;
    uVar2 = 0;
  }
  return uVar2;
}

