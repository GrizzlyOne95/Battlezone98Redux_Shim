
/* WARNING: Removing unreachable block (ram,0x007d53ae) */
/* WARNING: Removing unreachable block (ram,0x007d596a) */
/* WARNING: Removing unreachable block (ram,0x007d5d5a) */
/* WARNING: Removing unreachable block (ram,0x007d5e34) */
/* WARNING: Removing unreachable block (ram,0x007d5e6a) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_007d5120(char *param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  char *local_60;
  char *local_58;
  uint local_54;
  uint local_50;
  char *local_4c;
  char *local_48;
  undefined2 *local_44;
  char *local_40;
  char *local_3c;
  char *local_38;
  char *local_34;
  undefined4 local_30;
  char *local_2c;
  char *local_28;
  char *local_24;
  char *local_20;
  undefined4 local_1c;
  char *local_18;
  char *local_14;
  undefined1 local_d;
  undefined1 local_c;
  undefined1 local_b;
  undefined1 local_a;
  undefined1 local_9;
  char *local_8;
  
  if (param_1 == (char *)0x0) {
    FUN_007d65d0("This program must be launched from i76.exe\n");
  }
  FUN_007d6a70("Battlezone98 Command-Line: %s\n",param_1);
  local_8 = strtok(param_1,&DAT_008f068c);
  while (local_8 != (char *)0x0) {
    if (((*local_8 == '/') || (*local_8 == '-')) || (*local_8 == '+')) {
      iVar2 = _stricmp(local_8 + 1,"multi");
      if (iVar2 == 0) {
        _DAT_00920ed4 = 1;
      }
      else {
        iVar2 = _stricmp(local_8 + 1,"nomulti");
        if (iVar2 == 0) {
          _DAT_00920ed4 = 0xffffffff;
        }
        else {
          iVar2 = _stricmp(local_8 + 1,"win");
          if (iVar2 == 0) {
            FUN_00663d10(0);
          }
          else {
            iVar2 = _stricmp(local_8 + 1,"fullscreen");
            if (iVar2 == 0) {
              FUN_00663d10(1);
            }
            else {
              iVar2 = _stricmp(local_8 + 1,"rawinput");
              if (iVar2 == 0) {
                DAT_00918424 = 1;
              }
              else {
                iVar2 = _stricmp(local_8 + 1,"norawinput");
                if (iVar2 == 0) {
                  DAT_00918424 = 0;
                }
                else {
                  iVar2 = _stricmp(local_8 + 1,"noshell");
                  if (iVar2 == 0) {
                    DAT_0091556c = 1;
                  }
                  else {
                    iVar2 = _strnicmp(local_8 + 1,"flagfile:",9);
                    if (iVar2 == 0) {
                      local_58 = local_8 + 10;
                      local_3c = &DAT_00918404;
                      do {
                        cVar1 = *local_58;
                        *local_3c = cVar1;
                        local_58 = local_58 + 1;
                        local_3c = local_3c + 1;
                      } while (cVar1 != '\0');
                      local_a = 0;
                    }
                    else {
                      iVar2 = _strnicmp(local_8 + 1,"net:",4);
                      if ((iVar2 == 0) || (iVar2 = _strnicmp(local_8 + 1,"net=",4), iVar2 == 0)) {
                        local_48 = local_8 + 5;
                        local_1c = 0;
                        iVar2 = _stricmp(local_48,"steam");
                        if (iVar2 == 0) {
                          local_1c = 1;
                        }
                        else {
                          iVar2 = _stricmp(local_48,"gog");
                          if (iVar2 == 0) {
                            local_1c = 2;
                          }
                          else {
                            iVar2 = _stricmp(local_48,"cp");
                            if (iVar2 == 0) {
                              local_1c = 3;
                            }
                            else {
                              iVar2 = _stricmp(local_48,"bzr");
                              if (iVar2 == 0) {
                                local_1c = 4;
                              }
                            }
                          }
                        }
                        FUN_00764b20(local_1c);
                      }
                      else {
                        iVar2 = _strnicmp(local_8 + 1,"renderer:",9);
                        if ((iVar2 == 0) ||
                           (iVar2 = _strnicmp(local_8 + 1,"renderer=",9), iVar2 == 0)) {
                          FUN_00663d50(local_8 + 10);
                        }
                        else {
                          iVar2 = _strnicmp(local_8 + 1,"platform:",9);
                          if ((iVar2 == 0) ||
                             (iVar2 = _strnicmp(local_8 + 1,"platform=",9), iVar2 == 0)) {
                            pcVar4 = local_8 + 10;
                            local_30 = 0;
                            iVar2 = _stricmp(pcVar4,"win");
                            if (iVar2 == 0) {
                              local_30 = 0;
                            }
                            else {
                              iVar2 = _stricmp(pcVar4,"osx");
                              if (iVar2 == 0) {
                                local_30 = 1;
                              }
                              else {
                                iVar2 = _stricmp(pcVar4,"ios");
                                if (iVar2 == 0) {
                                  local_30 = 2;
                                }
                              }
                            }
                            FUN_004344b0(local_30);
                          }
                          else {
                            iVar2 = _stricmp(local_8 + 1,"resave");
                            if (iVar2 == 0) {
                              DAT_009183b4 = 1;
                            }
                            else {
                              iVar2 = _stricmp(local_8 + 1,"asciisave");
                              if (iVar2 == 0) {
                                DAT_008eaab4 = 0;
                              }
                              else {
                                iVar2 = _stricmp(local_8 + 1,"binarysave");
                                if (iVar2 == 0) {
                                  DAT_008eaab4 = 1;
                                }
                                else {
                                  iVar2 = _strnicmp(local_8 + 1,"shellmap",8);
                                  if (iVar2 == 0) {
                                    local_50 = 0x6c;
                                    local_54 = 0x59;
                                    iVar2 = sscanf(local_8 + 9,":%d,%d",&local_50,&local_54);
                                    if (iVar2 == 1) {
                                      local_54 = local_50;
                                    }
                                    DAT_009183d4 = 1;
                                    _DAT_009183c4 = local_54 << 0x10 | local_50;
                                  }
                                  else {
                                    iVar2 = _strnicmp(local_8 + 1,"largemap",8);
                                    if (iVar2 == 0) {
                                      DAT_009183d4 = 2;
                                      _DAT_009183c4 = 8;
                                      sscanf(local_8 + 9,":%d",&DAT_009183c4);
                                    }
                                    else {
                                      iVar2 = _stricmp(local_8 + 1,"nobodyhome");
                                      if (iVar2 == 0) {
                                        DAT_0091836c = 1;
                                      }
                                      else {
                                        iVar2 = _stricmp(local_8 + 1,"nointro");
                                        if (iVar2 == 0) {
                                          DAT_008eaab8 = 0;
                                        }
                                        else {
                                          iVar2 = _stricmp(local_8 + 1,"exitafterload");
                                          if (iVar2 == 0) {
                                            DAT_009183e8 = 1;
                                          }
                                          else {
                                            iVar2 = _stricmp(local_8 + 1,"saveafterload");
                                            if (iVar2 == 0) {
                                              DAT_009183bc = 1;
                                            }
                                            else {
                                              iVar2 = _stricmp(local_8 + 1,"edit");
                                              if (iVar2 == 0) {
                                                DAT_009454b8 = 1;
                                              }
                                              else {
                                                iVar2 = _stricmp(local_8 + 1,"startedit");
                                                if (iVar2 == 0) {
                                                  DAT_009183f4 = 1;
                                                  DAT_009454b8 = 1;
                                                }
                                                else {
                                                  iVar2 = _stricmp(local_8 + 1,"console");
                                                  if (iVar2 == 0) {
                                                    DAT_009183cc = 1;
                                                  }
                                                  else {
                                                    iVar2 = _stricmp(local_8 + 1,"develop");
                                                    if (iVar2 == 0) {
                                                      DAT_009183c8 = 1;
                                                    }
                                                    else {
                                                      iVar2 = _stricmp(local_8 + 1,"showunloc");
                                                      if (iVar2 == 0) {
                                                        DAT_00946724 = 1;
                                                      }
                                                      else {
                                                        iVar2 = _strnicmp(local_8 + 1,
                                                                          "connect_lobby",0xd);
                                                        if (iVar2 == 0) {
                                                          DAT_009183ec = 1;
                                                          local_14 = strrchr(local_8,0x3d);
                                                          if (local_14 != (char *)0x0) {
                                                            local_14 = local_14 + 1;
                                                            iVar2 = isdigit((int)*local_14);
                                                            if (iVar2 == 0) {
                                                              FUN_00765a20(local_14);
                                                            }
                                                            else {
                                                              FUN_00765ae0(local_14);
                                                            }
                                                          }
                                                        }
                                                        else {
                                                          iVar2 = _strnicmp(local_8 + 1,
                                                                            "connect-galaxy-lobby",
                                                                            0x14);
                                                          if (iVar2 == 0) {
                                                            DAT_009183ec = 1;
                                                            local_40 = strrchr(local_8,0x3d);
                                                            if (local_40 != (char *)0x0) {
                                                              local_40 = local_40 + 1;
                                                              FUN_00765a20(local_40);
                                                            }
                                                          }
                                                          else {
                                                            iVar2 = _strnicmp(local_8 + 1,
                                                                              "nickname=",9);
                                                            if (iVar2 == 0) {
                                                              strncpy(&DAT_009453e0,local_8 + 10,
                                                                      0x80);
                                                              DAT_0094545f = 0;
                                                            }
                                                            else {
                                                              iVar2 = _stricmp(local_8 + 1,
                                                                               "iorecord");
                                                              if (iVar2 == 0) {
                                                                DAT_00915554 = 1;
                                                              }
                                                              else {
                                                                iVar2 = _stricmp(local_8 + 1,
                                                                                 "noiorecord");
                                                                if (iVar2 == 0) {
                                                                  DAT_00915554 = 0;
                                                                }
                                                                else {
                                                                  iVar2 = _stricmp(local_8 + 1,
                                                                                   "netpktlog");
                                                                  if (iVar2 == 0) {
                                                                    if (DAT_009180d8 < 1) {
                                                                      DAT_009180d8 = 1;
                                                                    }
                                                                    DAT_00917f6c = 1;
                                                                  }
                                                                  else {
                                                                    iVar2 = _stricmp(local_8 + 1,
                                                                                     "nonetpktlog");
                                                                    if (iVar2 == 0) {
                                                                      DAT_009180d8 = 0;
                                                                      DAT_00917f6c = 0;
                                                                    }
                                                                    else {
                                                                      iVar2 = _stricmp(local_8 + 1,
                                                                                       "bzrnetlog");
                                                                      if (iVar2 == 0) {
                                                                        DAT_008eda28 = 1;
                                                                      }
                                                                      else {
                                                                        iVar2 = _strnicmp(local_8 + 
                                                  1,"bzrnetlog=",10);
                                                  if (iVar2 == 0) {
                                                    local_38 = strrchr(local_8,0x3d);
                                                    if (local_38 != (char *)0x0) {
                                                      local_38 = local_38 + 1;
                                                      DAT_008eda28 = atoi(local_38);
                                                    }
                                                  }
                                                  else {
                                                    iVar2 = _stricmp(local_8 + 1,"nobzrnetlog");
                                                    if (iVar2 == 0) {
                                                      DAT_008eda28 = 0;
                                                    }
                                                    else {
                                                      iVar2 = _stricmp(local_8 + 1,"netlog");
                                                      if (iVar2 == 0) {
                                                        DAT_009180d8 = 1;
                                                      }
                                                      else {
                                                        iVar2 = _stricmp(local_8 + 1,"netlog");
                                                        if (iVar2 == 0) {
                                                          DAT_009180d8 = 1;
                                                        }
                                                        else {
                                                          iVar2 = _strnicmp(local_8 + 1,"netlog=",7)
                                                          ;
                                                          if (iVar2 == 0) {
                                                            local_28 = strrchr(local_8,0x3d);
                                                            if (local_28 != (char *)0x0) {
                                                              local_28 = local_28 + 1;
                                                              DAT_009180d8 = atoi(local_28);
                                                            }
                                                          }
                                                          else {
                                                            iVar2 = _stricmp(local_8 + 1,"nonetlog")
                                                            ;
                                                            if (iVar2 == 0) {
                                                              DAT_009180d8 = 0;
                                                            }
                                                            else {
                                                              iVar2 = _stricmp(local_8 + 1,
                                                                               "nohgtsmoothing");
                                                              if (iVar2 == 0) {
                                                                DAT_009454cc = 1;
                                                              }
                                                              else {
                                                                iVar2 = _stricmp(local_8 + 1,
                                                                                 "dohgtsmoothing");
                                                                if (iVar2 == 0) {
                                                                  DAT_009454cc = 0;
                                                                }
                                                                else {
                                                                  iVar2 = _stricmp(local_8 + 1,
                                                                                                                                                                      
                                                  "enablerenderselection");
                                                  if (iVar2 == 0) {
                                                    DAT_008e7068 = 0;
                                                  }
                                                  else {
                                                    iVar2 = _stricmp(local_8 + 1,
                                                                     "disablerenderselection");
                                                    if (iVar2 == 0) {
                                                      DAT_008e7068 = 0;
                                                    }
                                                    else {
                                                      iVar2 = _stricmp(local_8 + 1,"disablemods");
                                                      if (iVar2 == 0) {
                                                        DAT_00915568 = 1;
                                                      }
                                                      else {
                                                        iVar2 = _stricmp(local_8 + 1,"iprelay");
                                                        if (iVar2 == 0) {
                                                          DAT_00946708 = 1;
                                                        }
                                                        else {
                                                          iVar2 = _stricmp(local_8 + 1,"ipdirect");
                                                          if (iVar2 == 0) {
                                                            DAT_00946708 = 0;
                                                          }
                                                          else {
                                                            iVar2 = _strnicmp(local_8 + 1,
                                                                              "bzrserver=",10);
                                                            if (iVar2 == 0) {
                                                              local_2c = strrchr(local_8,0x3d);
                                                              if (local_2c != (char *)0x0) {
                                                                local_2c = local_2c + 1;
                                                                strncpy(
                                                  s_ws___battlezone98mp_webdev_rebel_008f0690,
                                                  local_2c,0x1000);
                                                  DAT_008f168f = 0;
                                                  }
                                                  }
                                                  else {
                                                    iVar2 = _strnicmp(local_8 + 1,"bzrnetport=",0xb)
                                                    ;
                                                    if (iVar2 == 0) {
                                                      local_34 = strrchr(local_8,0x3d);
                                                      if (local_34 != (char *)0x0) {
                                                        local_34 = local_34 + 1;
                                                        iVar2 = atoi(local_34);
                                                        DAT_00945704 = (undefined2)iVar2;
                                                      }
                                                    }
                                                    else {
                                                      iVar2 = _strnicmp(local_8 + 1,"datadir=",8);
                                                      if ((iVar2 != 0) &&
                                                         (iVar2 = _stricmp(local_8 + 1,"zixlogindex"
                                                                          ), iVar2 == 0)) {
                                                        DAT_009467bc = 1;
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
      strncpy(&DAT_00945708,local_8,0x1000);
      DAT_00946707 = 0;
      strncpy(&DAT_00915540,local_8,0x10);
      DAT_0091554f = 0;
      local_18 = strrchr(&DAT_00945708,0x2e);
      if ((local_18 == (char *)0x0) || (iVar2 = _stricmp(local_18,".sav"), iVar2 != 0)) {
        FUN_00434170(5);
      }
      else {
        local_18 = strchr(&DAT_00945708,0x2f);
        if (local_18 == (char *)0x0) {
          local_18 = strchr(&DAT_00945708,0x5c);
        }
        if (local_18 == (char *)0x0) {
          local_60 = &DAT_02ceefe0;
          local_24 = &DAT_00945708;
          do {
            cVar1 = *local_60;
            *local_24 = cVar1;
            local_60 = local_60 + 1;
            local_24 = local_24 + 1;
          } while (cVar1 != '\0');
          local_44 = (undefined2 *)&DAT_00945707;
          do {
            pcVar4 = (char *)((int)local_44 + 1);
            local_44 = (undefined2 *)((int)local_44 + 1);
          } while (*pcVar4 != '\0');
          *local_44 = 0x5c;
          local_20 = local_8;
          do {
            cVar1 = *local_20;
            local_20 = local_20 + 1;
          } while (cVar1 != '\0');
          local_4c = &DAT_00945707;
          do {
            pcVar4 = local_4c + 1;
            local_4c = local_4c + 1;
          } while (*pcVar4 != '\0');
          pcVar4 = local_8;
          pcVar5 = local_4c;
          for (uVar3 = (uint)((int)local_20 - (int)local_8) >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
            *(undefined4 *)pcVar5 = *(undefined4 *)pcVar4;
            pcVar4 = pcVar4 + 4;
            pcVar5 = pcVar5 + 4;
          }
          uVar3 = (int)local_20 - (int)local_8 & 3;
          while( true ) {
            local_9 = 0;
            local_c = 0;
            local_d = 0;
            local_b = 0;
            if (uVar3 == 0) break;
            uVar3 = uVar3 - 1;
            *pcVar5 = *pcVar4;
            pcVar4 = pcVar4 + 1;
            pcVar5 = pcVar5 + 1;
          }
        }
        FUN_00434170(8);
      }
      DAT_0091556c = 1;
    }
    local_8 = strtok((char *)0x0,&DAT_008f068c);
  }
  return 1;
}

