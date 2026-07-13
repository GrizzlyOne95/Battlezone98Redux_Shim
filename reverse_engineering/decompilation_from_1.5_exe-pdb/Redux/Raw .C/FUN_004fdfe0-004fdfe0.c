
/* WARNING: Removing unreachable block (ram,0x004fe056) */

void FUN_004fdfe0(char *param_1,char *param_2,size_t param_3)

{
  undefined1 uVar1;
  undefined1 uVar2;
  FILE *_File;
  size_t _Count;
  void *pvVar3;
  size_t sVar4;
  undefined4 uVar5;
  char local_118;
  undefined1 local_117 [254];
  undefined1 uStack_19;
  char local_18 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_118 = '\0';
  memset(local_117,0,0xff);
  strncpy(&local_118,param_1,0x100);
  uStack_19 = 0;
  _File = fopen(&local_118,"rb");
  uVar2 = DAT_009173b7;
  uVar1 = DAT_009173b6;
  if (_File != (FILE *)0x0) {
    DAT_009173b6 = 0;
    DAT_009173b7 = 0;
    fseek(_File,0,2);
    _Count = ftell(_File);
    fseek(_File,0,0);
    pvVar3 = (void *)FUN_0083d92c(_Count);
    sVar4 = fread(pvVar3,1,_Count,_File);
    fclose(_File);
    uVar5 = FUN_004cdd10(pvVar3,_Count,sVar4);
    FUN_004ce910(uVar5,&DAT_00917b20,4);
    if (0x409 < DAT_00917b20) {
      FUN_004ce5e0(uVar5,&DAT_009173b6,1);
      FUN_004ce2f0(uVar5,local_18,0x10);
      if ((param_2 != (char *)0x0) && (param_3 != 0)) {
        strncpy(param_2,local_18,param_3);
        param_2[param_3 - 1] = '\0';
      }
      DAT_009173b6 = uVar1;
      DAT_009173b7 = uVar2;
      pvVar3 = (void *)FUN_004cdd70(uVar5);
      operator_delete__(pvVar3);
    }
  }
  FUN_0083e885();
  return;
}

