/*
 * Entry: 0048f8c1
 * Name: DistributedObject::ReceiveTempState
 * Namespace: DistributedObject
 * Signature: void ReceiveTempState(ushort param_1, char * param_2, uint param_3, float param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl
DistributedObject::ReceiveTempState(ushort param_1,char *param_2,uint param_3,float param_4)

{
  REDUCED_MAT RVar1;
  bool bVar2;
  byte bVar3;
  pair<unsigned_long_const_,DistributedObject_*> *ppVar4;
  DistributedObject *pDVar5;
  _OBJ76 *p_Var6;
  int iVar7;
  pair<unsigned_long_const_,float> *ppVar8;
  DistributedObject **ppDVar9;
  uint uVar10;
  MAT_3D *pMVar11;
  DistributedObject *pDVar12;
  uint uVar13;
  float *pfVar14;
  iterator iVar15;
  float fVar16;
  ulong uVar17;
  byte **ppbVar18;
  MAT_3D local_e0;
  float local_a0 [13];
  undefined1 local_6c [12];
  ulong local_60 [2];
  ulong local_58 [2];
  _Const_iterator<1> local_50;
  const_iterator local_48;
  const_iterator local_40;
  _Const_iterator<1> local_38;
  byte *local_30;
  const_iterator local_2c;
  byte *local_24;
  byte *local_20;
  byte local_19;
  undefined4 local_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined2 uStack_c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_6c;
  do {
    if ((param_3 < 6) || (*param_2 == 0)) {
      return;
    }
    local_20 = *(byte **)(param_2 + 2);
    bVar3 = param_2[1];
    ppbVar18 = &local_20;
    local_24 = (byte *)param_2;
    local_19 = bVar3;
    iVar15 = std::
             _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
             ::find((_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
                     *)&localDistributedObjectMap,local_60);
    local_2c._padding_ = *iVar15._0_4_;
    local_2c._Ptr = (_Node *)iVar15._0_4_[1];
    std::
    _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
    ::const_iterator::const_iterator
              (&local_40,(_Node *)localDistributedObjectMap._24_4_,
               (_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
                *)&localDistributedObjectMap);
    bVar2 = std::
            _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
            ::const_iterator::operator==(&local_2c,&local_40);
    if (bVar2) {
      pDVar12 = (DistributedObject *)0x0;
    }
    else {
      ppVar4 = std::
               _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
               ::const_iterator::operator*(&local_2c);
      pDVar12 = ppVar4->second;
    }
    if (pDVar12 == (DistributedObject *)0x0) {
      iVar15 = std::
               _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
               ::find((_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
                       *)&remoteDistributedObjectMap,local_58);
      local_2c._padding_ = *iVar15._0_4_;
      local_2c._Ptr = (_Node *)iVar15._0_4_[1];
      std::
      _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
      ::const_iterator::const_iterator
                (&local_48,(_Node *)remoteDistributedObjectMap._24_4_,
                 (_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
                  *)&remoteDistributedObjectMap);
      bVar2 = std::
              _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
              ::const_iterator::operator==(&local_2c,&local_48);
      if (bVar2) {
        pDVar12 = (DistributedObject *)0x0;
      }
      else {
        ppVar4 = std::
                 _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
                 ::const_iterator::operator*(&local_2c);
        pDVar12 = ppVar4->second;
      }
      if ((pDVar12 == (DistributedObject *)0x0) || ((local_19 & 3) != 2)) {
        if ((local_19 & 3) == 0) {
          if (pDVar12 == (DistributedObject *)0x0) {
            stdext::
            _Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>
            ::lower_bound((_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>
                           *)&delLocalIDMap,(ulong *)&local_38);
            std::
            list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
            ::_Const_iterator<1>::_Const_iterator<1>
                      (&local_50,(_Node *)delLocalIDMap._28_4_,
                       (list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
                        *)&delLocalIDMap.field_0x8);
            bVar2 = std::
                    list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
                    ::_Const_iterator<1>::operator==(&local_38,&local_50);
            if ((bVar2) ||
               (ppVar8 = std::
                         list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
                         ::_Const_iterator<1>::operator*(&local_38), ppVar8->second + 1.0 <= param_4
               )) {
              Create(param_1,param_2,param_3);
              ppDVar9 = std::
                        map<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>_>
                        ::operator[](&remoteDistributedObjectMap,(ulong *)&local_20);
              pDVar12 = *ppDVar9;
              if (pDVar12 != (DistributedObject *)0x0) goto LAB_0048fb37;
            }
          }
          else {
LAB_0048fb37:
            pDVar12->activnet_id = param_1;
            p_Var6 = (_OBJ76 *)(**(code **)(pDVar12->_padding_ + 0x30))();
            if (p_Var6 != (_OBJ76 *)0x0) {
              obj_clear_flag(p_Var6,0x200);
            }
            local_18 = *(undefined4 *)(param_2 + 6);
            uStack_14 = *(undefined4 *)(param_2 + 10);
            uStack_10 = *(undefined4 *)(param_2 + 0xe);
            uStack_c = *(undefined2 *)(param_2 + 0x12);
            if ((param_2[0x14] & 0x80U) == 0) {
              local_20 = local_24 + 0x1c;
            }
            else {
              local_20 = local_24 + 0x15;
            }
            param_2 = (char *)local_24;
            if (pDVar12->flast_received_time <= param_4) {
              pDVar12->flast_received_time = param_4;
              bVar2 = pDVar12->net_user;
              pDVar12->net_user = (bool)(local_19 >> 7);
              uVar13 = local_19 >> 2 & 0xf;
              if ((bVar2 != (bool)(local_19 >> 7)) ||
                 (uVar10 = (**(code **)(pDVar12->_padding_ + 4))(), uVar13 != uVar10)) {
                (**(code **)(pDVar12->_padding_ + 8))((short)uVar13);
              }
              RVar1.buf[4] = (undefined1)uStack_14;
              RVar1.buf[5] = uStack_14._1_1_;
              RVar1.buf[6] = uStack_14._2_1_;
              RVar1.buf[7] = uStack_14._3_1_;
              RVar1.buf[0] = (undefined1)local_18;
              RVar1.buf[1] = local_18._1_1_;
              RVar1.buf[2] = local_18._2_1_;
              RVar1.buf[3] = local_18._3_1_;
              RVar1.buf[8] = (undefined1)uStack_10;
              RVar1.buf[9] = uStack_10._1_1_;
              RVar1.buf[10] = uStack_10._2_1_;
              RVar1.buf[0xb] = uStack_10._3_1_;
              RVar1.buf[0xc] = (undefined1)uStack_c;
              RVar1.buf[0xd] = uStack_c._1_1_;
              pMVar11 = NetUtil_ExpandMatrix(&local_e0,RVar1);
              local_30 = local_24;
              pfVar14 = local_a0;
              for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
                *pfVar14 = pMVar11->right_x;
                pMVar11 = (MAT_3D *)&pMVar11->right_y;
                pfVar14 = pfVar14 + 1;
              }
              pDVar12->iter = 0.0;
              pDVar12->count = pDVar12->last_count;
              pDVar12->last_count = 0.0;
              pfVar14 = local_a0;
              pMVar11 = &pDVar12->true_transform;
              for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
                pMVar11->right_x = *pfVar14;
                pfVar14 = pfVar14 + 1;
                pMVar11 = (MAT_3D *)&pMVar11->right_y;
              }
              local_30 = local_30 + ((uint)*local_30 - (int)local_20);
              if (local_30 != (byte *)0x0) {
                (**(code **)(pDVar12->_padding_ + 0x40))(local_20,(short)&local_30);
              }
              fVar16 = Get_Time();
              local_20 = (byte *)(fVar16 - param_4);
              fVar16 = TimeStep();
              pDVar12->net_dt = (float)local_20 - fVar16;
              param_2 = (char *)local_24;
            }
          }
        }
        else {
          AiMission::GetCurrent();
          if (pDVar12 != (DistributedObject *)0x0) {
            *(undefined4 *)&pDVar12[1].true_transform.posit_y = 0;
            p_Var6 = (_OBJ76 *)(**(code **)(pDVar12->_padding_ + 0x30))();
            if ((local_19 & 0x40) == 0) {
              if (p_Var6 != (_OBJ76 *)0x0) {
                if ((local_19 & 0x3c) == 0) {
                  uVar17 = 0x280;
                }
                else {
                  uVar17 = 0x1000280;
                }
                obj_set_flag(p_Var6,uVar17);
              }
            }
            else {
              (**(code **)(pDVar12->_padding_ + 0x24))();
            }
            pDVar12->object_type = '\0';
            std::
            _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
            ::erase((_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
                     *)&remoteDistributedObjectMap,&pDVar12->dwLocalID);
            Destroy(pDVar12);
            iVar7 = (**(code **)pDVar12->_padding_)();
            if ((iVar7 != 0) && (*(int *)(iVar7 + 0x20) == 0x53435250)) {
              iVar7 = pDVar12->_padding_;
              goto LAB_0048f9c9;
            }
          }
        }
      }
    }
    else {
      bVar3 = bVar3 & 3;
      if (bVar3 == 2) {
        if (GameObject::userObject == (GameObject *)0x0) {
          pDVar5 = (DistributedObject *)0x0;
        }
        else {
          pDVar5 = (DistributedObject *)&GameObject::userObject->_padding_;
        }
        if (pDVar5 == pDVar12) {
          (**(code **)(*(int *)&pDVar12[-1].net_user + 0x7c))();
        }
        SetRemote(pDVar12);
        pDVar12->activnet_id = param_1;
      }
      else if (bVar3 == 3) {
        p_Var6 = (_OBJ76 *)(**(code **)(pDVar12->_padding_ + 0x30))((short)ppbVar18);
        if (p_Var6 != (_OBJ76 *)0x0) {
          obj_set_flag(p_Var6,0x200);
        }
        Destroy(pDVar12);
        iVar7 = (**(code **)pDVar12->_padding_)();
        if ((iVar7 != 0) && (*(int *)(iVar7 + 0x20) == 0x53435250)) {
          iVar7 = pDVar12->_padding_;
LAB_0048f9c9:
          (**(code **)(iVar7 + 0x10))();
        }
      }
    }
    param_3 = param_3 - (byte)*param_2;
    param_2 = param_2 + (byte)*param_2;
  } while( true );
}
