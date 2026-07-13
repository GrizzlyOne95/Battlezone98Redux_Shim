/*
 * Entry: 00504e99
 * Name: Device_Graphic_Init
 * Namespace: Global
 * Signature: VIDEO_DEVICE * Device_Graphic_Init(VIDEO_DEVICE * __return_storage_ptr__, void * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

VIDEO_DEVICE * __cdecl
Device_Graphic_Init(VIDEO_DEVICE *__return_storage_ptr__,void *param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  undefined4 *puVar3;
  int iVar4;
  int unaff_EBX;
  REFRESH_MODE unaff_ESI;
  VIDEO_DEVICE *pVVar5;
  WINDOW_MODE unaff_EDI;
  VIDEO_DEVICE *pVVar6;
  
  pcVar2 = param_2;
  do {
    cVar1 = *pcVar2;
    pcVar2[0xd42428 - (int)param_2] = cVar1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  Device.hInstance = param_1;
  Device.Screen_Width = GetSystemMetrics(0);
  Device.Screen_Height = GetSystemMetrics(1);
  puVar3 = (undefined4 *)&VideoMode;
  do {
    *puVar3 = 0;
    puVar3 = puVar3 + 8;
  } while ((int)puVar3 < 0x62e268);
  hiresEnable = GetPrivateProfileIntA("NormalView","HiRes",0,&cfgFileName);
  if (hiresEnable != 0) {
    _DAT_0062da94 = 8;
    _DAT_0062dab4 = 8;
    _DAT_0062dad4 = 8;
    _DAT_0062daf4 = 8;
  }
  if (useD3D != 0) {
    GetWin9xDisplayInfo();
    iVar4 = Init_D3D_Device(&Device,param_2);
    if (iVar4 != 0) goto LAB_00504fa1;
    (*Device.VideoMode.close)(&Device);
    if (LastErrorString[0] == '\0') {
      pcVar2 = "Running software rendering mode";
    }
    else {
      pcVar2 = LastErrorString;
    }
    MessageBoxA((HWND)0x0,pcVar2,"Failed to init 3D hardware acceleration",0);
    useD3D = 0;
    D3IniFlags = 0;
  }
  Device_Set_Graphic_Mode((VIDEO_DEVICE *)(uint)(UseDDraw == 0),0,unaff_EDI,unaff_ESI,unaff_EBX);
  Device_Init_Luminance_Table(&Device,(char *)0x0);
  Device_Init_Chrome_Key_Table(&Device);
  _DAT_0062db08 = 1;
LAB_00504fa1:
  pVVar5 = &Device;
  pVVar6 = __return_storage_ptr__;
  for (iVar4 = 0xfe; iVar4 != 0; iVar4 = iVar4 + -1) {
    (pVVar6->Viewport).Width = (pVVar5->Viewport).Width;
    pVVar5 = (VIDEO_DEVICE *)&(pVVar5->Viewport).Height;
    pVVar6 = (VIDEO_DEVICE *)&(pVVar6->Viewport).Height;
  }
  return __return_storage_ptr__;
}
