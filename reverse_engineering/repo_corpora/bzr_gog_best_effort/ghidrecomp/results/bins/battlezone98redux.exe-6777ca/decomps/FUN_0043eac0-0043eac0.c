
void FUN_0043eac0(void)

{
  int local_8;
  
  FUN_0081e1e0("Shutting down music handler\n");
  SetEvent(DAT_0260cacc);
  for (local_8 = 0; local_8 < 2; local_8 = local_8 + 1) {
    while ((&DAT_0260cdd4)[local_8 * 0x310] == '\0') {
      MsgWaitForMultipleObjects(1,(HANDLE *)&DAT_00915648,0,0xffffffff,0);
    }
  }
  for (local_8 = 0; local_8 < 2; local_8 = local_8 + 1) {
    CloseHandle(*(HANDLE *)(&DAT_0260cac8 + local_8 * 0x310));
    CloseHandle(*(HANDLE *)(&DAT_0260cad4 + local_8 * 0x310));
    if ((&DAT_0260cad9)[local_8 * 0x310] != '\0') {
      (&DAT_0260cad9)[local_8 * 0x310] = 0;
      ov_clear(&DAT_0260cae8 + local_8 * 0x310);
      memset(&DAT_0260cae8 + local_8 * 0x310,0,0x2d0);
      FUN_007d6a70("Stopping Music Playback Index %d During Music Shutdown\n",local_8);
    }
    if (*(int *)(&DAT_0260cae4 + local_8 * 0x310) != 0) {
      if (*(undefined4 **)(&DAT_0260cae4 + local_8 * 0x310) != (undefined4 *)0x0) {
        (**(code **)**(undefined4 **)(&DAT_0260cae4 + local_8 * 0x310))(1);
      }
      *(undefined4 *)(&DAT_0260cae4 + local_8 * 0x310) = 0;
    }
    DeleteCriticalSection((LPCRITICAL_SECTION)(&DAT_0260cdbc + local_8 * 0x310));
  }
  CloseHandle(DAT_0260cacc);
  FUN_0081e1e0("Shut down music handler\n");
  return;
}

