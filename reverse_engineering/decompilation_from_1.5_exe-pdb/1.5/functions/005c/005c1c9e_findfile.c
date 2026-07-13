/*
 * Entry: 005c1c9e
 * Name: findfile
 * Namespace: Global
 * Signature: char * findfile(lua_State * param_1, char * param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl findfile(lua_State *param_1,char *param_2,char *param_3)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  FILE *_File;
  lua_State *unaff_EBX;
  char *pcVar5;
  char *pcVar6;
  
  pcVar2 = luaL_gsub(unaff_EBX,(char *)param_1,".","\\");
  lua_getfield(unaff_EBX,-0x2711,param_2);
  pcVar3 = lua_tolstring(unaff_EBX,-1,(uint *)0x0);
  if (pcVar3 == (char *)0x0) {
    luaL_error(unaff_EBX,"\'package.%s\' must be a string");
  }
  lua_pushlstring(unaff_EBX,"",0);
  while( true ) {
    cVar1 = *pcVar3;
    pcVar5 = pcVar3;
    while (cVar1 == ';') {
      pcVar5 = pcVar5 + 1;
      cVar1 = *pcVar5;
    }
    if (*pcVar5 == '\0') {
      return (char *)0x0;
    }
    pcVar3 = strchr(pcVar5,0x3b);
    pcVar4 = pcVar5;
    if (pcVar3 == (char *)0x0) {
      do {
        pcVar3 = pcVar4;
        pcVar4 = pcVar3 + 1;
      } while (*pcVar3 != '\0');
    }
    lua_pushlstring(unaff_EBX,pcVar5,(int)pcVar3 - (int)pcVar5);
    if (pcVar3 == (char *)0x0) break;
    pcVar6 = "?";
    pcVar5 = pcVar2;
    pcVar4 = lua_tolstring(unaff_EBX,-1,(uint *)0x0);
    pcVar5 = luaL_gsub(unaff_EBX,pcVar4,pcVar6,pcVar5);
    lua_remove(unaff_EBX,-2);
    _File = fopen(pcVar5,"r");
    if (_File != (FILE *)0x0) {
      fclose(_File);
      return pcVar5;
    }
    lua_pushfstring(unaff_EBX,"\n\tno file \'%s\'");
    lua_remove(unaff_EBX,-2);
    lua_concat(unaff_EBX,2);
  }
  return (char *)0x0;
}
