/*
 * Entry: 00546488
 * Name: ProcessCommandLine
 * Namespace: Global
 * Signature: int ProcessCommandLine(char * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ProcessCommandLine(char *param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  int iVar4;
  char *pcVar5;
  uint local_8;
  uint local_4;
  
  if (param_1 == (char *)0x0) {
    DEBUG_systemError("This program must be launched from i76.exe\n");
  }
  pcVar2 = strtok(param_1,commandDelims);
  AddonFirst = 1;
  do {
    if (pcVar2 == (char *)0x0) {
      return 1;
    }
    if ((*pcVar2 == '/') || (*pcVar2 == '-')) {
      pcVar5 = pcVar2 + 1;
      iVar4 = _stricmp(pcVar5,"team");
      if (iVar4 == 0) {
        pcVar2 = strtok((char *)0x0,commandDelims);
        iVar4 = atoi(pcVar2);
        Net_SetTeam(iVar4);
      }
      else {
        iVar4 = _stricmp(pcVar5,"soviet");
        if (iVar4 == 0) {
          Net_SetSoviet();
        }
        else {
          iVar4 = _stricmp(pcVar5,"netshell");
          if (iVar4 == 0) {
            Net_DoNetworking(1);
            Net_SetNetShell();
          }
          else {
            iVar4 = _stricmp(pcVar5,"net");
            if (iVar4 == 0) {
              Net_DoNetworking(1);
            }
            else {
              iVar4 = _stricmp(pcVar5,"join");
              if (iVar4 == 0) {
                pcVar2 = strtok((char *)0x0,commandDelims);
                Net_DoNetworking(1);
                iVar4 = 0;
LAB_00546607:
                Net_Hosting(iVar4);
                Net_SetGameName(pcVar2);
              }
              else {
                iVar4 = _stricmp(pcVar5,"odf");
                if (iVar4 == 0) {
                  pcVar2 = strtok((char *)0x0,commandDelims);
                  Net_SetODF(pcVar2);
                }
                else {
                  iVar4 = _stricmp(pcVar5,"load");
                  if (iVar4 == 0) {
                    pcVar2 = strtok((char *)0x0,commandDelims);
                    pcVar5 = &loadFilename;
                    do {
                      cVar1 = *pcVar2;
                      pcVar2 = pcVar2 + 1;
                      *pcVar5 = cVar1;
                      pcVar5 = pcVar5 + 1;
                    } while (cVar1 != '\0');
                    doload = 1;
                  }
                  else {
                    iVar4 = _stricmp(pcVar5,"host");
                    if (iVar4 == 0) {
                      pcVar2 = strtok((char *)0x0,commandDelims);
                      Net_DoNetworking(1);
                      iVar4 = 1;
                      goto LAB_00546607;
                    }
                    iVar4 = _stricmp(pcVar5,"deathmatch");
                    if (iVar4 == 0) {
                      Net_SetDeathMatch(1);
                    }
                    else {
                      iVar4 = _stricmp(pcVar5,"players");
                      if (iVar4 == 0) {
LAB_00546695:
                        strtok((char *)0x0,commandDelims);
                      }
                      else {
                        iVar4 = _stricmp(pcVar5,"name");
                        if (iVar4 == 0) {
                          pcVar2 = strtok((char *)0x0,commandDelims);
                          Net_SetPlayerName(pcVar2);
                        }
                        else {
                          iVar4 = _stricmp(pcVar5,"transport");
                          if (iVar4 == 0) {
                            pcVar2 = strtok((char *)0x0,commandDelims);
                            Net_SetTransport(pcVar2);
                          }
                          else {
                            iVar4 = _stricmp(pcVar5,"server");
                            if ((iVar4 == 0) || (iVar4 = _stricmp(pcVar5,"comm"), iVar4 == 0))
                            goto LAB_00546695;
                            iVar4 = _stricmp(pcVar5,"gdi");
                            if ((iVar4 == 0) || (iVar4 = _stricmp(pcVar5,"win"), iVar4 == 0)) {
                              UseDDraw = 0;
                            }
                            else {
                              iVar4 = _stricmp(pcVar5,"rawinput");
                              if (iVar4 == 0) {
                                UseRawInput = 1;
                              }
                              else {
                                iVar4 = _stricmp(pcVar5,"norawinput");
                                if (iVar4 == 0) {
                                  UseRawInput = 0;
                                }
                                else {
                                  iVar4 = _stricmp(pcVar5,"demo");
                                  if (iVar4 == 0) {
                                    nDemoFlag = 1;
                                  }
                                  else {
                                    iVar4 = _stricmp(pcVar5,"D3D");
                                    if (iVar4 == 0) {
                                      useD3D = 1;
                                    }
                                    else {
                                      iVar4 = _stricmp(pcVar5,"SW");
                                      if (iVar4 == 0) {
                                        useD3D = 0;
                                      }
                                      else {
                                        iVar4 = _stricmp(pcVar5,"noshell");
                                        if (iVar4 == 0) {
                                          NoShell = 1;
                                        }
                                        else {
                                          iVar4 = _stricmp(pcVar5,"gamesetup");
                                          if (iVar4 == 0) {
                                            bGameSetup = 1;
                                          }
                                          else {
                                            iVar4 = _strnicmp(pcVar5,"flagfile:",9);
                                            if (iVar4 == 0) {
                                              pcVar2 = pcVar2 + 10;
                                              iVar4 = (int)&sFlagFileName - (int)pcVar2;
                                              do {
                                                cVar1 = *pcVar2;
                                                pcVar2[iVar4] = cVar1;
                                                pcVar2 = pcVar2 + 1;
                                              } while (cVar1 != '\0');
                                            }
                                            else {
                                              iVar4 = _stricmp(pcVar5,"addon");
                                              if (iVar4 == 0) {
                                                AddonFirst = (int)(AddonFirst == 0);
                                              }
                                              else {
                                                iVar4 = _stricmp(pcVar5,"resave");
                                                if (iVar4 == 0) {
                                                  Resave = 1;
                                                }
                                                else {
                                                  iVar4 = _stricmp(pcVar5,"asciisave");
                                                  if (iVar4 == 0) {
                                                    BinarySave = 0;
                                                  }
                                                  else {
                                                    iVar4 = _stricmp(pcVar5,"binarysave");
                                                    if (iVar4 == 0) {
                                                      BinarySave = 1;
                                                    }
                                                    else {
                                                      iVar4 = _strnicmp(pcVar5,"shellmap",8);
                                                      if (iVar4 == 0) {
                                                        local_8 = 0x6c;
                                                        local_4 = 0x59;
                                                        iVar4 = sscanf(pcVar2 + 9,":%d,%d",&local_8,
                                                                       &local_4);
                                                        uVar3 = local_8;
                                                        if (iVar4 != 1) {
                                                          uVar3 = local_4;
                                                        }
                                                        DumpTerrainArg = uVar3 << 0x10 | local_8;
                                                        DumpTerrain = 1;
                                                      }
                                                      else {
                                                        iVar4 = _strnicmp(pcVar5,"largemap",8);
                                                        if (iVar4 == 0) {
                                                          DumpTerrain = 2;
                                                          DumpTerrainArg = 8;
                                                          sscanf(pcVar2 + 9,":%d",&DumpTerrainArg);
                                                        }
                                                        else {
                                                          iVar4 = _stricmp(pcVar5,"nobodyhome");
                                                          if (iVar4 == 0) {
                                                            NobodyHome = 1;
                                                          }
                                                          else {
                                                            iVar4 = _stricmp(pcVar5,"nointro");
                                                            if (iVar4 == 0) {
                                                              playIntro = 0;
                                                            }
                                                            else {
                                                              iVar4 = _stricmp(pcVar5,"forcefeed");
                                                              if (iVar4 == 0) {
                                                                AllowForceFeedback();
                                                              }
                                                              else {
                                                                iVar4 = _stricmp(pcVar5,"nods");
                                                                if (iVar4 == 0) {
                                                                  UseAudio = 0;
                                                                }
                                                                else {
                                                                  iVar4 = _stricmp(pcVar5,"nods3d");
                                                                  if (iVar4 == 0) {
                                                                    UseDS3DAudio = 0;
                                                                  }
                                                                  else {
                                                                    iVar4 = _stricmp(pcVar5,"netdbg"
                                                                                    );
                                                                    if (iVar4 == 0) {
                                                                      NetworkDebug = 1;
                                                                    }
                                                                    else {
                                                                      iVar4 = _stricmp(pcVar5,
                                                  "showreg");
                                                  if (iVar4 == 0) {
                                                    ShowRegens = 1;
                                                  }
                                                  else {
                                                    iVar4 = _stricmp(pcVar5,"edit");
                                                    if (iVar4 == 0) {
                                                      TerrainEdit = 1;
                                                    }
                                                    else {
                                                      iVar4 = _stricmp(pcVar5,"startedit");
                                                      if (iVar4 == 0) {
                                                        StartEdit = 1;
                                                        TerrainEdit = 1;
                                                      }
                                                      else {
                                                        iVar4 = _stricmp(pcVar5,"console");
                                                        if (iVar4 == 0) {
                                                          UseConsole = 1;
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
    else {
      iVar4 = (int)param_2 - (int)pcVar2;
      do {
        cVar1 = *pcVar2;
        pcVar2[iVar4] = cVar1;
        pcVar2 = pcVar2 + 1;
      } while (cVar1 != '\0');
      Net_SetMissionFile(param_2);
    }
    pcVar2 = strtok((char *)0x0,commandDelims);
  } while( true );
}
