/*
 * Entry: 0040a76f
 * Name: BlockCells
 * Namespace: Global
 * Signature: void BlockCells(GameObject * param_1, bool param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl BlockCells(GameObject *param_1,bool param_2)

{
  int *piVar1;
  const_iterator cVar2;
  const_iterator cVar3;
  GameObject *pGVar4;
  bool bVar5;
  int iVar6;
  _OBJ76 *p_Var7;
  MAT_3D *pMVar8;
  Area *pAVar9;
  pair<GameObject_*_const,Area> *ppVar10;
  float fVar11;
  float fVar12;
  undefined3 in_stack_00000009;
  VECTOR_3D *pVVar13;
  VECTOR_3D *pVVar14;
  VECTOR_3D local_2c;
  VECTOR_3D local_20;
  const_iterator local_14;
  const_iterator local_c;
  
  pGVar4 = param_1;
  if (cellType != (uchar *)0x0) {
    piVar1 = &param_1->_padding_;
    iVar6 = (**(code **)*piVar1)();
    if (*(int *)(iVar6 + 0x28) == 5) {
      iVar6 = (*(code *)((undefined4 *)*piVar1)[0xb])();
      local_2c.z = *(float *)(iVar6 + 0x44);
      local_20.x = *(float *)(iVar6 + 0x4c);
      local_20.y = *(float *)(iVar6 + 0x50);
      local_20.z = *(float *)(iVar6 + 0x58);
      if (param_2 == false) {
        std::
        _Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
        ::find((_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
                *)&perimeterArea,(GameObject **)&local_c);
        std::
        _Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
        ::const_iterator::const_iterator
                  (&local_14,(_Node *)perimeterArea._24_4_,
                   (_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
                    *)&perimeterArea);
        bVar5 = std::
                _Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
                ::const_iterator::operator==(&local_c,&local_14);
        if (!bVar5) {
          ppVar10 = std::
                    _Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
                    ::const_iterator::operator*(&local_c);
          local_2c.z = (ppVar10->second).x0;
          local_20.x = (ppVar10->second).z0;
          local_20.y = (ppVar10->second).x1;
          local_20.z = (ppVar10->second).z1;
          cVar3._Ptr = (_Node *)local_c._padding_;
          cVar3._padding_ = (int)&local_14;
          std::
          _Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
          ::erase((_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
                   *)&perimeterArea,cVar3);
        }
      }
      else {
        pAVar9 = std::
                 map<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>_>
                 ::operator[](&perimeterArea,&param_1);
        pAVar9->x0 = local_2c.z;
        pAVar9->z0 = local_20.x;
        pAVar9->x1 = local_20.y;
        pAVar9->z1 = local_20.z;
      }
      PerimeterCells(local_2c.z,local_20.x,local_20.y,local_20.z,SUB41(_param_2,0));
    }
    else {
      (**(code **)*piVar1)();
      pVVar14 = &local_20;
      pVVar13 = &local_2c;
      p_Var7 = (_OBJ76 *)(**(code **)(*piVar1 + 0x30))();
      get_obj_bounding_box(p_Var7,pVVar13,pVVar14);
      p_Var7 = pGVar4->obj;
      pMVar8 = &p_Var7->transform;
      blockVertCount = 4;
      blockVertArray[0].x =
           pMVar8->right_x * local_2c.x + (p_Var7->transform).front_x * local_2c.z +
           (float)(p_Var7->transform).posit_x;
      blockVertArray[0].z =
           (p_Var7->transform).right_z * local_2c.x + (p_Var7->transform).front_z * local_2c.z +
           (float)(p_Var7->transform).posit_z;
      blockVertArray[1].x =
           (p_Var7->transform).front_x * local_2c.z + pMVar8->right_x * local_20.x +
           (float)(p_Var7->transform).posit_x;
      blockVertArray[1].z =
           (p_Var7->transform).right_z * local_20.x + (p_Var7->transform).front_z * local_2c.z +
           (float)(p_Var7->transform).posit_z;
      blockVertArray[2].x =
           pMVar8->right_x * local_20.x + (p_Var7->transform).front_x * local_20.z +
           (float)(p_Var7->transform).posit_x;
      blockVertArray[2].z =
           (p_Var7->transform).front_z * local_20.z + (p_Var7->transform).right_z * local_20.x +
           (float)(p_Var7->transform).posit_z;
      blockVertArray[3].x =
           (p_Var7->transform).front_x * local_20.z + pMVar8->right_x * local_2c.x +
           (float)(p_Var7->transform).posit_x;
      blockVertArray[3].z =
           (p_Var7->transform).front_z * local_20.z + (p_Var7->transform).right_z * local_2c.x +
           (float)(p_Var7->transform).posit_z;
      fVar11 = Min(blockVertArray[2].x,blockVertArray[3].x);
      fVar12 = Min(blockVertArray[0].x,blockVertArray[1].x);
      local_2c.z = Min(fVar12,fVar11);
      fVar11 = Min(blockVertArray[2].z,blockVertArray[3].z);
      fVar12 = Min(blockVertArray[0].z,blockVertArray[1].z);
      local_20.x = Min(fVar12,fVar11);
      fVar11 = Max(blockVertArray[2].x,blockVertArray[3].x);
      fVar12 = Max(blockVertArray[0].x,blockVertArray[1].x);
      local_20.y = Max(fVar12,fVar11);
      fVar11 = Max(blockVertArray[2].z,blockVertArray[3].z);
      fVar12 = Max(blockVertArray[0].z,blockVertArray[1].z);
      local_20.z = Max(fVar12,fVar11);
      if (param_2 == false) {
        std::
        _Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
        ::find((_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
                *)&buildingArea,(GameObject **)&local_c);
        std::
        _Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
        ::const_iterator::const_iterator
                  (&local_14,(_Node *)buildingArea._24_4_,
                   (_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
                    *)&buildingArea);
        bVar5 = std::
                _Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
                ::const_iterator::operator==(&local_c,&local_14);
        if (!bVar5) {
          ppVar10 = std::
                    _Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
                    ::const_iterator::operator*(&local_c);
          local_2c.z = (ppVar10->second).x0;
          local_20.x = (ppVar10->second).z0;
          local_20.y = (ppVar10->second).x1;
          local_20.z = (ppVar10->second).z1;
          cVar2._Ptr = (_Node *)local_c._padding_;
          cVar2._padding_ = (int)&local_14;
          std::
          _Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
          ::erase((_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
                   *)&buildingArea,cVar2);
        }
      }
      else {
        pAVar9 = std::
                 map<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>_>
                 ::operator[](&buildingArea,&param_1);
        pAVar9->x0 = local_2c.z;
        pAVar9->z0 = local_20.x;
        pAVar9->x1 = local_20.y;
        pAVar9->z1 = local_20.z;
      }
      BuildingCells(local_2c.z,local_20.x,local_20.y,local_20.z,SUB41(_param_2,0));
      blockVertCount = 0;
    }
  }
  return;
}
