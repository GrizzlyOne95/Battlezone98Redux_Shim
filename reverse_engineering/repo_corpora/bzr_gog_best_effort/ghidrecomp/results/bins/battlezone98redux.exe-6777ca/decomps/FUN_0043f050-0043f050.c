
int FUN_0043f050(undefined4 param_1,undefined4 param_2,undefined1 param_3)

{
  int iVar1;
  int local_10;
  int local_c;
  
  local_c = -1;
  local_10 = 0;
  do {
    if (1 < local_10) {
LAB_0043f091:
      if ((local_c < 0) || (1 < local_c)) {
        FUN_007d6a70("Max ogg stream count of %d exceeded, requested sound will not play :(\n",2);
        local_c = -1;
      }
      else {
        FUN_007d6a70("Starting Music Playback Index %d\n",local_c);
        *(undefined4 *)(&DAT_0260cadc + local_c * 0x310) = param_1;
        *(undefined4 *)(&DAT_0260cae0 + local_c * 0x310) = param_2;
        (&DAT_0260cad8)[local_c * 0x310] = param_3;
        *(undefined4 *)(&DAT_0260cdb8 + local_c * 0x310) = 0;
        iVar1 = ov_open_callbacks(&DAT_0260cac8 + local_c * 0x310,&DAT_0260cae8 + local_c * 0x310,0,
                                  0,PTR_FUN_008e7664,PTR_FUN_008e7668,PTR__Val_type<>_008e766c,
                                  PTR_FUN_008e7670);
        if (iVar1 < 0) {
          FUN_007d6a70(
                      "OggManager::Setup - ov_open_callbacks failed. Requested audio will not play :("
                      );
          local_c = -1;
        }
        else {
          if (*(int *)(&DAT_0260cae4 + local_c * 0x310) != 0) {
            if (*(undefined4 **)(&DAT_0260cae4 + local_c * 0x310) != (undefined4 *)0x0) {
              (**(code **)**(undefined4 **)(&DAT_0260cae4 + local_c * 0x310))(1);
            }
            *(undefined4 *)(&DAT_0260cae4 + local_c * 0x310) = 0;
          }
          iVar1 = FUN_0043ec90(&DAT_0260cae4 + local_c * 0x310,&DAT_0260cae8 + local_c * 0x310,
                               0x10188,0,0,0,0,0x10,*(undefined4 *)(&DAT_0260cac8 + local_c * 0x310)
                              );
          if (iVar1 < 0) {
            ov_clear(&DAT_0260cae8 + local_c * 0x310);
            FUN_007d6a70("Couldn\'t create a streaming ogg!\n");
            local_c = -1;
          }
          else {
            (&DAT_0260cad9)[local_c * 0x310] = 1;
          }
        }
      }
      return local_c;
    }
    if ((&DAT_0260cad9)[local_10 * 0x310] == '\0') {
      local_c = local_10;
      goto LAB_0043f091;
    }
    local_10 = local_10 + 1;
  } while( true );
}

