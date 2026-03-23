
undefined4 __fastcall FUN_006aa310(int *param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  uVar1 = SteamAPI_GetHSteamUser();
  iVar2 = SteamAPI_GetHSteamPipe(uVar1);
  if (iVar2 == 0) {
    uVar1 = 0;
  }
  else {
    iVar3 = SteamInternal_CreateInterface("SteamClient017");
    *param_1 = iVar3;
    if (*param_1 == 0) {
      uVar1 = 0;
    }
    else {
      iVar3 = (**(code **)(*(int *)*param_1 + 0x14))(uVar1,iVar2,"SteamUser019");
      param_1[1] = iVar3;
      if (param_1[1] == 0) {
        uVar1 = 0;
      }
      else {
        iVar3 = (**(code **)(*(int *)*param_1 + 0x20))(uVar1,iVar2,"SteamFriends015");
        param_1[2] = iVar3;
        if (param_1[2] == 0) {
          uVar1 = 0;
        }
        else {
          iVar3 = (**(code **)(*(int *)*param_1 + 0x24))(iVar2,"SteamUtils008");
          param_1[3] = iVar3;
          if (param_1[3] == 0) {
            uVar1 = 0;
          }
          else {
            iVar3 = (**(code **)(*(int *)*param_1 + 0x28))(uVar1,iVar2,"SteamMatchMaking009");
            param_1[4] = iVar3;
            if (param_1[4] == 0) {
              uVar1 = 0;
            }
            else {
              iVar3 = (**(code **)(*(int *)*param_1 + 0x2c))
                                (uVar1,iVar2,"SteamMatchMakingServers002");
              param_1[7] = iVar3;
              if (param_1[7] == 0) {
                uVar1 = 0;
              }
              else {
                iVar3 = (**(code **)(*(int *)*param_1 + 0x34))
                                  (uVar1,iVar2,"STEAMUSERSTATS_INTERFACE_VERSION011");
                param_1[5] = iVar3;
                if (param_1[5] == 0) {
                  uVar1 = 0;
                }
                else {
                  iVar3 = (**(code **)(*(int *)*param_1 + 0x3c))
                                    (uVar1,iVar2,"STEAMAPPS_INTERFACE_VERSION008");
                  param_1[6] = iVar3;
                  if (param_1[6] == 0) {
                    uVar1 = 0;
                  }
                  else {
                    iVar3 = (**(code **)(*(int *)*param_1 + 0x40))(uVar1,iVar2,"SteamNetworking005")
                    ;
                    param_1[8] = iVar3;
                    if (param_1[8] == 0) {
                      uVar1 = 0;
                    }
                    else {
                      iVar3 = (**(code **)(*(int *)*param_1 + 0x44))
                                        (uVar1,iVar2,"STEAMREMOTESTORAGE_INTERFACE_VERSION014");
                      param_1[9] = iVar3;
                      if (param_1[9] == 0) {
                        uVar1 = 0;
                      }
                      else {
                        iVar3 = (**(code **)(*(int *)*param_1 + 0x48))
                                          (uVar1,iVar2,"STEAMSCREENSHOTS_INTERFACE_VERSION003");
                        param_1[10] = iVar3;
                        if (param_1[10] == 0) {
                          uVar1 = 0;
                        }
                        else {
                          iVar3 = (**(code **)(*(int *)*param_1 + 0x5c))
                                            (uVar1,iVar2,"STEAMHTTP_INTERFACE_VERSION002");
                          param_1[0xb] = iVar3;
                          if (param_1[0xb] == 0) {
                            uVar1 = 0;
                          }
                          else {
                            iVar3 = (**(code **)(*(int *)*param_1 + 0x60))
                                              (uVar1,iVar2,
                                               "STEAMUNIFIEDMESSAGES_INTERFACE_VERSION001");
                            param_1[0xc] = iVar3;
                            if (param_1[0xc] == 0) {
                              uVar1 = 0;
                            }
                            else {
                              iVar3 = (**(code **)(*(int *)*param_1 + 100))
                                                (uVar1,iVar2,"SteamController004");
                              param_1[0xd] = iVar3;
                              if (param_1[0xd] == 0) {
                                uVar1 = 0;
                              }
                              else {
                                iVar3 = (**(code **)(*(int *)*param_1 + 0x68))
                                                  (uVar1,iVar2,"STEAMUGC_INTERFACE_VERSION009");
                                param_1[0xe] = iVar3;
                                if (param_1[0xe] == 0) {
                                  uVar1 = 0;
                                }
                                else {
                                  iVar3 = (**(code **)(*(int *)*param_1 + 0x6c))
                                                    (uVar1,iVar2,"STEAMAPPLIST_INTERFACE_VERSION001"
                                                    );
                                  param_1[0xf] = iVar3;
                                  if (param_1[0xf] == 0) {
                                    uVar1 = 0;
                                  }
                                  else {
                                    iVar3 = (**(code **)(*(int *)*param_1 + 0x70))
                                                      (uVar1,iVar2,"STEAMMUSIC_INTERFACE_VERSION001"
                                                      );
                                    param_1[0x10] = iVar3;
                                    if (param_1[0x10] == 0) {
                                      uVar1 = 0;
                                    }
                                    else {
                                      iVar3 = (**(code **)(*(int *)*param_1 + 0x74))
                                                        (uVar1,iVar2,
                                                         "STEAMMUSICREMOTE_INTERFACE_VERSION001");
                                      param_1[0x11] = iVar3;
                                      if (param_1[0x11] == 0) {
                                        uVar1 = 0;
                                      }
                                      else {
                                        iVar3 = (**(code **)(*(int *)*param_1 + 0x78))
                                                          (uVar1,iVar2,
                                                           "STEAMHTMLSURFACE_INTERFACE_VERSION_003")
                                        ;
                                        param_1[0x12] = iVar3;
                                        if (param_1[0x12] == 0) {
                                          uVar1 = 0;
                                        }
                                        else {
                                          iVar3 = (**(code **)(*(int *)*param_1 + 0x88))
                                                            (uVar1,iVar2,
                                                             "STEAMINVENTORY_INTERFACE_V001");
                                          param_1[0x13] = iVar3;
                                          if (param_1[0x13] == 0) {
                                            uVar1 = 0;
                                          }
                                          else {
                                            iVar2 = (**(code **)(*(int *)*param_1 + 0x8c))
                                                              (uVar1,iVar2,
                                                               "STEAMVIDEO_INTERFACE_V001");
                                            param_1[0x14] = iVar2;
                                            if (param_1[0x14] == 0) {
                                              uVar1 = 0;
                                            }
                                            else {
                                              uVar1 = 1;
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
    }
  }
  return uVar1;
}

