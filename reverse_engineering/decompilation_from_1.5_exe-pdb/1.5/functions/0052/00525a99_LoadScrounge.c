/*
 * Entry: 00525a99
 * Name: LoadScrounge
 * Namespace: Global
 * Signature: long LoadScrounge(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

long __cdecl LoadScrounge(char *param_1)

{
  char *pcVar1;
  long lVar2;
  ENTITY_LOADER local_2e8;
  StructObjectType local_294;
  char local_21c [4];
  char local_218 [256];
  char local_118 [256];
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&local_294.TransformMatrix.posit_x;
  if (*param_1 != '\0') {
    memset(&local_2e8,0,0x54);
    memset(&local_294,0,0x78);
    local_294.BoxHalfHeightX = 50.0;
    local_294.BoxHalfHeightY = 50.0;
    local_294.BoxHalfHeightZ = 50.0;
    local_294.Class = 0xb;
    _splitpath(param_1,local_21c,local_218,local_18,local_118);
    strncpy((char *)&local_294,local_18,8);
    local_2e8.entObj = NewObj((_OBJ76 *)0x0,&local_294,&local_294.GeometryFile,0);
    if (local_2e8.entObj != (_OBJ76 *)0x0) {
      AddTerrainSpecial(local_2e8.entObj);
      pcVar1 = PrjID2Filename(CONCAT44(local_294.GeometryFile._4_4_,
                                       (undefined4)local_294.GeometryFile),".sdf");
      lVar2 = LoadStructure(&local_294,&local_2e8,pcVar1);
      return lVar2;
    }
  }
  return 0;
}
