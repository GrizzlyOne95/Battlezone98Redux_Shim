/*
 * Entry: 0041a55b
 * Name: LoadValue
 * Namespace: Global
 * Signature: void LoadValue(_iobuf * param_1, lua_State * param_2, bool param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

void __cdecl LoadValue(_iobuf *param_1,lua_State *param_2,bool param_3,int param_4)

{
  MAT_3D *pMVar1;
  VECTOR_3D *pVVar2;
  char *pcVar3;
  int iVar4;
  MAT_3D *pMVar5;
  lua_State *unaff_EDI;
  MAT_3D local_5c;
  undefined1 local_1c [8];
  float fStack_14;
  void *local_10;
  bool local_a;
  uchar local_9;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  in(param_1,&local_9,1);
  local_9 = local_9 + 0xd0;
  if (local_9 == '\x01') {
    in(param_1,&local_a,1);
    pcVar3 = "true";
    if (local_a == false) {
      pcVar3 = "false";
    }
    Trace(pcVar3);
    if (param_3) {
      lua_pushboolean(param_2,(uint)local_a);
    }
  }
  else if (local_9 == '\x02') {
    in(param_1,(int *)&local_10,4);
    local_10 = (void *)ConvertHandle((int)local_10);
    Trace("%08X");
    if (param_3) {
      lua_pushlightuserdata(param_2,local_10);
    }
  }
  else if (local_9 == '\x03') {
    in(param_1,(double *)(local_1c + 4),8);
    Trace("%f");
    if (param_3) {
      lua_pushnumber(param_2,(double)CONCAT44(unaff_EDI,fStack_14));
    }
  }
  else if (local_9 == '\x04') {
    in(param_1,(int *)&fStack_14,4);
    iVar4 = -((int)fStack_14 + 1);
    *(float *)(&stack0xffffff94 + iVar4) = fStack_14;
    *(undefined1 **)(&stack0xffffff90 + iVar4) = &stack0xffffff98 + iVar4;
    *(_iobuf **)(&stack0xffffff8c + iVar4) = param_1;
    *(undefined4 *)(&stack0xffffff88 + iVar4) = 0x41a79c;
    in(*(_iobuf **)(&stack0xffffff8c + iVar4),*(char **)(&stack0xffffff90 + iVar4),
       *(uint *)(&stack0xffffff94 + iVar4));
    *(undefined1 **)(&stack0xffffff88 + iVar4) = &stack0xffffff98 + iVar4;
    *(char **)(&stack0xffffff84 + iVar4) = "\"%s\"";
    *(undefined4 *)(&stack0xffffff80 + iVar4) = 0x41a7a7;
    Trace(*(char **)(&stack0xffffff84 + iVar4));
    if (param_3) {
      *(float *)(&stack0xffffff94 + iVar4) = fStack_14;
      *(undefined1 **)(&stack0xffffff90 + iVar4) = &stack0xffffff98 + iVar4;
      *(lua_State **)(&stack0xffffff8c + iVar4) = param_2;
      *(undefined4 *)(&stack0xffffff88 + iVar4) = 0x41a7c0;
      lua_pushlstring(*(lua_State **)(&stack0xffffff8c + iVar4),*(char **)(&stack0xffffff90 + iVar4)
                      ,*(uint *)(&stack0xffffff94 + iVar4));
    }
  }
  else if (local_9 == '\x05') {
    in(param_1,(int *)&fStack_14,4);
    lua_createtable(param_2,0,0);
    Trace("{");
    local_10 = (void *)0x0;
    if (0 < (int)fStack_14) {
      do {
        Trace("\n%.*s[");
        LoadValue(param_1,param_2,param_3,param_4 + 1);
        Trace("]=");
        LoadValue(param_1,param_2,param_3,param_4 + 1);
        if (param_3) {
          lua_rawset(param_2,-3);
        }
        local_10 = (void *)((int)local_10 + 1);
      } while ((int)local_10 < (int)fStack_14);
    }
    Trace("\n%.*s}");
  }
  else if (local_9 == '\a') {
    in(param_1,(ulong *)&local_10,4);
    if (local_10 == (void *)0xe3f3088) {
      in(param_1,(VECTOR_3D *)local_1c,0xc);
      Trace("{x=%f,y=%f,z=%f}");
      if (param_3) {
        pVVar2 = NewVector(unaff_EDI);
        pVVar2->x = (float)local_1c._0_4_;
        pVVar2->y = (float)local_1c._4_4_;
        pVVar2->z = fStack_14;
      }
    }
    else if (local_10 == (void *)0x247e1851) {
      in(param_1,&local_5c,0x40);
      Trace(
           "{right_x=%f, right_y=%f, right_z=%f, up_x=%f, up_y=%f, up_z=%f, front_x=%f, front_y=%f, front_z=%f, posit_x=%f, posit_y=%f, posit_z=%f}"
           );
      if (param_3) {
        pMVar1 = NewMatrix(unaff_EDI);
        pMVar5 = &local_5c;
        for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
          pMVar1->right_x = pMVar5->right_x;
          pMVar5 = (MAT_3D *)&pMVar5->right_y;
          pMVar1 = (MAT_3D *)&pMVar1->right_y;
        }
      }
    }
  }
  else {
    Trace("nil");
    if (param_3) {
      lua_pushnil(param_2);
    }
  }
  return;
}
