
int FUN_0061df70(char *param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *local_24;
  char *local_20;
  char *local_1c;
  char *local_18;
  int local_14;
  int local_10;
  
  local_10 = 0;
  do {
    iVar2 = DAT_0091a364;
    if (3 < local_10) {
      local_24 = param_1;
      iVar4 = DAT_0091a364 * 0x28;
      DAT_0091a364 = DAT_0091a364 + 1;
      local_1c = &DAT_0091a368 + iVar4;
      do {
        cVar1 = *local_24;
        *local_1c = cVar1;
        local_24 = local_24 + 1;
        local_1c = local_1c + 1;
      } while (cVar1 != '\0');
      (&DAT_0091a434)[iVar2] = 0;
      FUN_00621820(0x6e,0,param_1,&DAT_0091a368 + iVar4);
      return -1;
    }
    if (((&PTR_PTR_008eadb0)[local_10] != (undefined *)0x0) &&
       (iVar2 = (**(code **)(&PTR_PTR_008eadb0)[local_10])(), iVar2 != 0)) {
      for (local_14 = 0; iVar4 = DAT_0091a364, local_14 < iVar2; local_14 = local_14 + 1) {
        if (4 < DAT_0091a364) {
          FUN_007d6830("Too many input devices specified");
          return -1;
        }
        iVar3 = (**(code **)((&PTR_PTR_008eadb0)[local_10] + 4))
                          (local_14,&DAT_0091ff10 + DAT_0091a364 * 0x74);
        if (iVar3 == 0) {
          iVar3 = _stricmp(&DAT_0091ff10 + iVar4 * 0x74,param_1);
          if (iVar3 == 0) {
            local_20 = param_1;
            local_18 = &DAT_0091a368 + iVar4 * 0x28;
            do {
              cVar1 = *local_20;
              *local_18 = cVar1;
              local_20 = local_20 + 1;
              local_18 = local_18 + 1;
            } while (cVar1 != '\0');
            (&DAT_0091fefc)[iVar4] = (&PTR_PTR_008eadb0)[local_10];
            DAT_0091a364 = DAT_0091a364 + 1;
            iVar2 = (**(code **)((&DAT_0091fefc)[iVar4] + 8))(&DAT_0091ff10 + iVar4 * 0x74);
            if (iVar2 != 0) {
              FUN_00621820(0x70,0,&DAT_0091ff1c + iVar4 * 0x74);
              (&DAT_0091a434)[iVar4] = 0;
              return -1;
            }
            (&DAT_0091a434)[iVar4] = 1;
            return iVar4;
          }
          (**(code **)((&PTR_PTR_008eadb0)[local_10] + 0xc))(&DAT_0091ff10 + iVar4 * 0x74);
        }
      }
    }
    local_10 = local_10 + 1;
  } while( true );
}

