/*
 * Entry: 00479534
 * Name: WinMain
 * Namespace: Global
 * Signature: int WinMain(HINSTANCE__ * param_1, HINSTANCE__ * param_2, char * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Enum "LOCALE": Some values do not have unique names */

int __cdecl WinMain(HINSTANCE__ *param_1,HINSTANCE__ *param_2,char *param_3,int param_4)

{
  HWND hWnd;
  LPVOID lpAddress;
  LPCSTR lpText;
  int iVar1;
  FILE *pFVar2;
  VIDEO_DEVICE *pVVar3;
  HANDLE pvVar4;
  BOOL BVar5;
  long lVar6;
  COORD CVar7;
  undefined4 *puVar8;
  code *pcVar9;
  VIDEO_DEVICE *pVVar10;
  __time64_t _Var11;
  char *pcVar12;
  int iVar13;
  UINT uType;
  size_t sVar14;
  DWORD dwPriorityClass;
  COORD local_66c;
  HINSTANCE local_668;
  tagMSG local_664;
  WNDCLASSA local_648;
  undefined4 local_620 [8];
  VIDEO_DEVICE local_600;
  undefined1 local_208 [260];
  char local_104 [256];
  uint local_4;
  
  local_4 = __security_cookie ^ (uint)&local_66c;
  local_668 = (HINSTANCE)param_1;
  ExitCode = 0;
  _controlfp(0,0x18);
  getcwd(local_208,0x104);
  memset(&Device,0,0x3f8);
  shell_hInstance = param_1;
  _DAT_00224566 = _StrLookupCreate("lang.txt");
  hWnd = FindWindowA("Battlezone 1.5.2.27 Update 1",(LPCSTR)0x0);
  if (hWnd == (HWND)0x0) {
    lpAddress = VirtualAlloc((LPVOID)0x0,0x1e00000,0x1000,4);
    if (lpAddress == (LPVOID)0x0) {
      uType = 0x10;
      pcVar12 = "Battlezone";
      lpText = (LPCSTR)_StrLookupFind(_DAT_00224566,"Not Enough Swap File Space");
      MessageBoxA((HWND)Device.hwndApp,lpText,pcVar12,uType);
                    /* WARNING: Subroutine does not return */
      exit(0x97);
    }
    VirtualFree(lpAddress,0,0x8000);
    InitMachineCaps((MACHINE_CAPS *)&local_664);
    Mono_Init();
    dmeminit();
    dmem_permanent();
    strncpy(local_104,param_3,0xff);
    msn_filename = '\0';
    ShowRegens = 0;
    iVar1 = ProcessCommandLine(param_3,&msn_filename);
    if (iVar1 == 0) {
      DEBUG_systemError("BattleZone found incorrect command line arguments");
    }
    if (UseConsole != 0) {
      local_664.hwnd._0_2_ = 0;
      local_664.hwnd._2_2_ = 0;
      local_664.message = 0x18004f;
      local_66c.X = 0x50;
      local_66c.Y = 1000;
      AllocConsoleIfNeeded();
      console_stdout = GetStdHandle(0xfffffff5);
      OpenConsoleBuffer(console_stdout,"Battlezone Console");
      SetConsoleWindowInfo(console_stdout,1,(SMALL_RECT *)&local_664);
      SetConsoleScreenBufferSize(console_stdout,local_66c);
      pcVar12 = "w";
      iVar1 = _open_osfhandle((intptr_t)console_stdout,0x4000);
      local_66c = (COORD)_fdopen(iVar1,pcVar12);
      CVar7 = local_66c;
      puVar8 = local_620;
      for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar8 = *(undefined4 *)CVar7;
        CVar7 = (COORD)((int)CVar7 + 4);
        puVar8 = puVar8 + 1;
      }
      pFVar2 = __iob_func();
      sVar14 = 0;
      iVar13 = 4;
      pcVar12 = (char *)0x0;
      puVar8 = local_620;
      pFVar2 = pFVar2 + 1;
      for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
        pFVar2->_ptr = (char *)*puVar8;
        puVar8 = puVar8 + 1;
        pFVar2 = (FILE *)&pFVar2->_cnt;
      }
      pFVar2 = __iob_func();
      setvbuf(pFVar2 + 1,pcVar12,iVar13,sVar14);
      CVar7 = local_66c;
      puVar8 = local_620;
      for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar8 = *(undefined4 *)CVar7;
        CVar7 = (COORD)((int)CVar7 + 4);
        puVar8 = puVar8 + 1;
      }
      pFVar2 = __iob_func();
      sVar14 = 0;
      iVar13 = 4;
      pcVar12 = (char *)0x0;
      puVar8 = local_620;
      pFVar2 = pFVar2 + 2;
      for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
        pFVar2->_ptr = (char *)*puVar8;
        puVar8 = puVar8 + 1;
        pFVar2 = (FILE *)&pFVar2->_cnt;
      }
      pFVar2 = __iob_func();
      setvbuf(pFVar2 + 2,pcVar12,iVar13,sVar14);
      param_1 = (HINSTANCE__ *)local_668;
    }
    NoShell = (int)(msn_filename != '\0');
    saveload = doload;
    doload = 0;
    _Var11 = _time64((__time64_t *)0x0);
    srand((uint)_Var11);
    Init_normal_vector_table();
    InitPaletteGammas();
    LoadUserProfile();
    set_joystick();
    InitForceFeedback();
    if (param_2 == (HINSTANCE__ *)0x0) {
      local_648.style = 3;
      local_648.lpfnWndProc = WindowProc;
      local_648.cbClsExtra = 0;
      local_648.cbWndExtra = 4;
      local_648.hInstance = (HINSTANCE)param_1;
      local_648.hIcon = LoadIconA((HINSTANCE)param_1,&DAT_000000bc);
      local_648.hCursor = LoadCursorA((HINSTANCE)0x0,&DAT_00007f00);
      local_648.hbrBackground = GetStockObject(4);
      local_648.lpszMenuName = (LPCSTR)0x0;
      local_648.lpszClassName = "Battlezone 1.5.2.27 Update 1";
      RegisterClassA(&local_648);
    }
    else {
      DEBUG_systemError("BattleZone is already running");
    }
    Vertex_Pool = VirtualAlloc((LPVOID)0x0,0x400000,0x3000,4);
    Quadtree_Cell_Pool = VirtualAlloc((LPVOID)0x0,0x80000,0x3000,4);
    if ((Quadtree_Cell_Pool == (LPVOID)0x0) || (Vertex_Pool == (VECTOR_3D *)0x0)) {
      DEBUG_systemError("Unable Allocate Virtual Memory, aborting Program...");
    }
    GetLastSessionFlag();
    memset(&Device,0,0x3f8);
    pVVar3 = Device_Graphic_Init(&local_600,param_1,"Battlezone 1.5.2.27 Update 1");
    pVVar10 = &Device;
    for (iVar1 = 0xfe; iVar1 != 0; iVar1 = iVar1 + -1) {
      (pVVar10->Viewport).Width = (pVVar3->Viewport).Width;
      pVVar3 = (VIDEO_DEVICE *)&(pVVar3->Viewport).Height;
      pVVar10 = (VIDEO_DEVICE *)&(pVVar10->Viewport).Height;
    }
    if (Device.Error != NO_DEVICE_ERROR) {
      DEBUG_systemError("BattleZone Init_Graphic_System");
    }
    iVar1 = (*Device.VideoMode.ChangeMode)(&Device,0);
    if (iVar1 == 0) {
      DEBUG_systemError("BattleZone Init_Graphic_System");
    }
    FirstResource();
    LoadLibraryA("RICHED20.DLL");
    InitLocale();
    SetNetworkFont((HWND__ *)0x0);
    InitKeyboard(LocaleInfo->KeyNames,LocaleInfo->KeyDescriptions);
    InitSimFonts(&Device);
    LockMouse();
    if (UseRawInput != 0) {
      local_664.hwnd._0_2_ = 1;
      local_664.hwnd._2_2_ = 2;
      local_664.message = 0;
      local_664.wParam = 0;
      UseRawInput = RegisterRawInputDevices((PCRAWINPUTDEVICE)&local_664,1,0xc);
    }
    set_sys_cursor();
    if (nDemoFlag != 0) {
      nDemoState = 1;
      do {
        HandleMessageQueue(&Device);
        do_demo_screen(0);
      } while (nDemoState != 0);
    }
    movie_initialize();
    nCDFlag = IntroMovieExists();
    pcVar9 = SetFocus_exref;
    if (nCDFlag == 0) {
      playIntro = 0;
    }
    if ((playIntro != 0) && (iVar1 = movie_open("intro.avi"), iVar1 != 0)) {
      GetClientRect((HWND)shell_hwnd,(LPRECT)&gameWindow);
      SetFocus((HWND)shell_hwnd);
      nMCIcheck = movie_play(0,&gameWindow);
      if (nMCIcheck != 0) {
        iVar1 = -2;
        pvVar4 = GetCurrentThread();
        SetThreadPriority(pvVar4,iVar1);
        ScreenMode = SCREENMODE_MOVIE;
        while (iVar1 = movie_is_playing(), iVar1 != 0) {
          HandleMessageQueue(&Device);
        }
        iVar1 = 0;
        pvVar4 = GetCurrentThread();
        SetThreadPriority(pvVar4,iVar1);
      }
    }
    task_bar = (HWND__ *)FindWindowA("Shell_TrayWnd",(LPCSTR)0x0);
    SetWindowPos((HWND)task_bar,(HWND)0x1,0,0,0,0,0x13);
    runningSS = 5;
    ResetScreenMode();
    LoadUserProfile();
    if (StartEdit != 0) {
      UserProfilePtr->playOption = UserProfilePtr->playOption | 1;
    }
    GameFeature_InitAll();
    FirstGAS(Device.hwndApp);
    while( true ) {
      if (bGameSetup == 0) {
        if (((runningSS == 5) || (runningSS == 2)) && (NoShell == 0)) {
          while( true ) {
            while( true ) {
              clear_events();
              iVar1 = (*Device.VideoMode.ChangeMode)(&Device,0);
              if (iVar1 == 0) {
                DEBUG_systemError("BattleZone Init_Graphic_System");
              }
              set_sys_cursor();
              clear_events();
              ShowWindow((HWND)shell_hwnd,9);
              BlackOutScreen(Black_Color);
              StartMusic(0xc,1);
              do_smain();
              StopMusic();
              clear_events();
              if (nPlayCredits == 0) break;
              nPlayCredits = 0;
              do_credits_movie();
            }
            if (nReplayIntro == 0) break;
            nReplayIntro = 0;
            LastGAS();
            iVar1 = movie_open("intro.avi");
            if (iVar1 != 0) {
              GetClientRect((HWND)shell_hwnd,(LPRECT)&gameWindow);
              (*pcVar9)(shell_hwnd);
              nMCIcheck = movie_play(0,&gameWindow);
              if (nMCIcheck != 0) {
                iVar1 = -2;
                pvVar4 = GetCurrentThread();
                SetThreadPriority(pvVar4,iVar1);
                ScreenMode = SCREENMODE_MOVIE;
                while (iVar1 = movie_is_playing(), iVar1 != 0) {
                  HandleMessageQueue(&Device);
                }
                iVar1 = 0;
                pvVar4 = GetCurrentThread();
                SetThreadPriority(pvVar4,iVar1);
              }
            }
            FirstGAS(Device.hwndApp);
          }
        }
      }
      else if (runningSS == 5) {
        clear_events();
        ShowWindow((HWND)shell_hwnd,9);
        iVar1 = do_gamesetup();
        if (iVar1 == 0) {
          runningSS = 10;
        }
        clear_events();
      }
      if ((runningSS == 10) || ((runningSS == 2 && ((NoShell != 0 || (bGameSetup != 0)))))) break;
      if (runningSS == 7) {
        iVar1 = 0;
        do {
          pcVar12 = &msn_filename + iVar1;
          (&loadFilename)[iVar1] = *pcVar12;
          iVar1 = iVar1 + 1;
        } while (*pcVar12 != '\0');
LAB_00479c21:
        runningSS = 5;
      }
      else {
        if (runningSS == 9) goto LAB_00479c21;
        if (runningSS == 5) {
          iVar1 = 0;
          do {
            pcVar12 = &msn_filename + iVar1;
            (&loadFilename)[iVar1] = *pcVar12;
            iVar1 = iVar1 + 1;
          } while (*pcVar12 != '\0');
        }
      }
      chdir(local_208);
      GamePaletteLoaded = 0;
      WindowsPaletteLoaded = 0;
      SetCBState(1);
      dmem_temporary();
      Init_Pseudo_Rand();
      Time_Init();
      FirstInputs();
      Init_Object_Database();
      world_init();
      SetResolutionFont();
      InitWrappers();
      Scroll_Init();
      TextInput_Init();
      if (NoShell == 0) {
        iVar1 = (*Device.VideoMode.ChangeMode)(&Device,0);
        if (iVar1 == 0) {
          DEBUG_systemError("BattleZone Init_Graphic_System");
        }
        ShowWindow((HWND)shell_hwnd,9);
        (*pcVar9)(shell_hwnd);
        clear_events();
        nLoadBitmapStatus = 1;
        set_cursor(2);
        draw_load_bitmap();
        noPaint = 1;
      }
      Device_Set_Chrome_Key(&Device,0xff);
      Init_FrameRate_and_TargetPosition();
      ZSORTInit();
      InitTerrainSpecials();
      GeoCache_Init();
      Texture_Init();
      TexAnim_Init();
      Shadow_Init();
      AnimObj_Init();
      ReadSpriteTableFile();
      InitCollisions();
      InitClassHandler();
      DisplayInterface_Init();
      AI_Init();
      GameFeature_PreLoadAll();
      Collision_Configure();
      doload = 0;
      difficultySetting = (UserProfilePtr->config).difficulty;
      iVar1 = LoadGame(&loadFilename);
      if (iVar1 == 0) {
        runningSS = 2;
      }
      else {
        (UserProfilePtr->config).difficulty = difficultySetting;
        while (iVar1 = check_load_voice(), iVar1 != 0) {
          BVar5 = PeekMessageA(&local_664,(HWND)0x0,0x100,0x109,0);
          if (BVar5 != 0) {
            HandleMessageQueue(&Device);
          }
          NextGAS(0);
        }
        TerrainSaveName(&msn_filename);
        doload = 1;
        CreateBuildings = 1;
        DisplayInterface_LoadColors();
        AI_PostLoad();
        ClassFirstFunctions();
        Collision_Create_Range_Search_Structure();
        GameObject_InitRange();
        Scrap_InitRange();
        if (doload == 0) {
          AI_CreateMission();
        }
        doload = 0;
        saveload = 0;
        CheckResaveMission();
        iVar1 = Net_IsNetGame();
        if (iVar1 != 0) {
          Net_Create();
          PostLoadGame();
          iVar1 = Net_Execute();
          if (iVar1 == 0) {
            runningSS = 2;
            goto LAB_0047a2b0;
          }
          Trace("Waiting for network system...\n");
          do_wait_for_net();
          do {
            SetLoopTimes();
            iVar1 = Net_Execute();
            if ((iVar1 == 0) || (iVar1 = did_user_stop_net(), iVar1 != 0)) {
              runningSS = 2;
              break;
            }
            Sleep(10);
            iVar1 = Net_IsNotRunning();
          } while (iVar1 != 0);
          do_finish_for_net();
          Trace("Network ready\n");
          Net_CreateMission();
        }
        GameFeature_PostLoadAll();
        DisplayInterface_PostLoad();
        if (DumpTerrain == 1) {
          DumpShellMapBMP(&msn_filename,DumpTerrainArg & 0xffff,(uint)DumpTerrainArg >> 0x10);
        }
        else if (DumpTerrain == 2) {
          DumpLargeMapBMP(&msn_filename,DumpTerrainArg);
        }
        ShowWindow((HWND)shell_hwnd,9);
        (*pcVar9)(shell_hwnd);
        nLoadBitmapStatus = 0;
        noPaint = 0;
        set_cursor(1);
        lVar6 = Get_Closest_RGB_Entry(0.0,0.0,0.0);
        BlackOutScreen(lVar6);
        (*Device.VideoMode.writePaletteEntries)
                  (&Device,0,0x100,(RGB *)&Default_Palette,(char *)Luminance_Table);
        Init_Sky();
        Black_Color = Get_Closest_RGB_Entry(0.0,0.0,0.0);
        Init_FPS();
        LockMouse();
        set_world_global_entities_quality();
        StopMusic();
        ClearKeyboardState();
        StartMusic(-1,0);
        clear_events();
        iVar1 = (*Device.VideoMode.ChangeMode)
                          (&Device,(uint)(UserProfilePtr->graphicDetail).resolution);
        if (iVar1 == 0) {
          DEBUG_systemError("BattleZone Init_Graphic_System");
        }
        set_sys_cursor();
        clear_events();
        ShowWindow((HWND)shell_hwnd,9);
        (*pcVar9)(shell_hwnd);
        Init_View_Record(1);
        iVar1 = Cache_Create_Bsp_Heap(0x40000);
        if (iVar1 == 0) {
                    /* WARNING: Subroutine does not return */
          I76FatalError((char *)0x0);
        }
        iVar1 = Net_IsNetGame();
        if ((iVar1 == 0) && (View_Record.Update_Camera != (_func___cdecl_void *)0x0)) {
          (*View_Record.Update_Camera)();
        }
        OverlayDefaultPalette(0,0x100,0);
        lVar6 = Get_Closest_RGB_Entry(0.0,0.0,0.0);
        BlackOutScreen(lVar6);
        GamePaletteLoaded = 1;
        EnableForceFeedback();
        ClearForceFeedback();
        Resume();
        iVar1 = Net_IsNetGame();
        if (iVar1 != 0) {
          Net_DoSyncStart();
        }
        MainLoopRunning = 1;
        while (runningSS == 5) {
          (*DoNextFrame)();
        }
        MainLoopRunning = 0;
        if ((TerrainEdit != 0) && (TerrainEditMode != 0)) {
          TerrainEditMode = 0;
          TerrainWireFrame = 0;
          SetEditMode(0);
          SelectTerrainView(0);
          UserProfilePtr->playOption = UserProfilePtr->playOption & 0xfffffffe;
        }
        SaveUserProfile();
        dwPriorityClass = 0x20;
        pvVar4 = GetCurrentProcess();
        SetPriorityClass(pvVar4,dwPriorityClass);
        iVar1 = 0;
        pvVar4 = GetCurrentThread();
        SetThreadPriority(pvVar4,iVar1);
        iVar1 = runningSS;
        StopMusic();
        if (iVar1 == 1) {
          Fade_Last_Frame(0.01,0x20,0,0,0);
          BlackOutScreen(Black_Color);
          do_success_mission();
        }
        else if ((iVar1 == 0) || (iVar1 == 0xb)) {
          Fade_Last_Frame(0.01,0x20,0,0,0);
          BlackOutScreen(Black_Color);
          do_fail_mission();
        }
        else {
          Fade_Last_Frame(0.01,0x20,0,0,0);
          BlackOutScreen(Black_Color);
        }
        StopActiveList();
        Cache_Delete_Bsp_Heap();
        ClassLastFunctions();
        UnlockMouse();
        ClearForceFeedback();
        DisableForceFeedback();
        LastInputs();
        Time_Done();
        Close_Terrain_Texture_Info();
        Destroy_Light_Model();
        DisplayInterface_Cleanup();
        Close_Sky();
        FreeTerrainSpecials();
        AnimObj_Close();
        DeleteClassHandler();
        Collision_Trash_Range_Search_Structure();
        GameObject_CleanupRange();
        Scrap_CleanupRange();
        Ordnance_Clean();
        GameFeature_PreDestroyAll();
        GameObject_Clean();
        Weapon_Clean();
        Terrain_Close();
        PurgeGASLists();
        SetCBState(0);
        world_destroy();
        DeleteCollisionHandler();
        TexAnim_Cleanup();
        AI_Cleanup();
        GameFeature_PostRunAll();
        ExplosionClass_Clean();
        OrdnanceClass_Clean();
        WeaponClass_Clean();
        GameObjectClass_Clean();
        Init_Object_Database();
        Shadow_Cleanup();
        Texture_Cleanup();
        GeoCache_Cleanup();
        ZSORTTerminate();
        obj_heap_destroy();
        iVar13 = Net_IsNetGame();
        if (iVar13 != 0) {
          Net_Delete();
        }
        DestroyWrappers();
        TextInput_Cleanup();
        Scroll_Cleanup();
        dmem_deletetemp();
        dmem_permanent();
        if ((((NoShell == 0) && (iVar1 != 7)) && (iVar1 != 10)) && (iVar1 != 9)) {
          ResetScreenMode();
          LoadUserProfile();
        }
        chdir(local_208);
        pcVar9 = SetFocus_exref;
      }
    }
    Net_Delete();
    Net_Close();
    if (nDemoFlag != 0) {
      do_demo_screen(1);
      nDemoState = 1;
      do {
        HandleMessageQueue(&Device);
      } while (nDemoState != 0);
    }
    reset_cursor();
    UnlockMouse();
    SetCDVolume(nSaveVolume);
    ShowWindow((HWND)task_bar,1);
LAB_0047a2b0:
    GameFeature_CleanupAll();
    movie_shutdown();
    ReleaseSprites();
    VirtualFree(Quadtree_Cell_Pool,0,0x8000);
    VirtualFree(Vertex_Pool,0,0x8000);
    FreeSimFonts(&Device);
    if (Default_Font != (FONT *)0x0) {
      Font_Free(Default_Font);
    }
    if (J_Font != (FONT *)0x0) {
      Font_Free(J_Font);
    }
    LastResource();
    SetLastSessionFlag();
    CloseForceFeedback();
    FreeUserProfile();
    _StrLookupDestroy(_DAT_00224566);
    cleanup_before_exit();
    dmemcleanup();
    Mono_Cleanup();
    iVar1 = ExitCode;
  }
  else {
    ShowWindow(hWnd,9);
    iVar1 = 0;
  }
  return iVar1;
}
