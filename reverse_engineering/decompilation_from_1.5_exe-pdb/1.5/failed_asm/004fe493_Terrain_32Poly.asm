; Entry: 004fe493
; Name: Terrain_32Poly
; Signature: void Terrain_32Poly(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
; Stop: 0x004fed59
; Reason: Exception while decompiling 004fe493: process: timeout 
; Command: C:\Program Files\LLVM\bin\llvm-objdump.EXE -d --no-show-raw-insn --start-address=0x004fe493 --stop-address=0x004fed59 C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe


C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe:	file format coff-i386

Disassembly of section .text:

00401000 <.text>:
  4fe493:      	pushl	%ebp
  4fe494:      	movl	%esp, %ebp
  4fe496:      	pushl	%ebx
  4fe497:      	pushl	%esi
  4fe498:      	pushl	%edi
  4fe499:      	pushl	%ebp
  4fe49a:      	subl	$0x700, %esp            # imm = 0x700
  4fe4a0:      	movl	0x14(%ebp), %ebx
  4fe4a3:      	movl	$0x186a0, %edx          # imm = 0x186A0
  4fe4a8:      	movl	0xc(%ebp), %esi
  4fe4ab:      	movl	0x10(%ebp), %eax
  4fe4ae:      	fildl	0x4(%ebx)
  4fe4b1:      	movl	(%ebx), %ecx
  4fe4b3:      	movl	%esi, (%esp)
  4fe4b6:      	shll	$0x3, %eax
  4fe4b9:      	leal	0x8(%ebx), %edi
  4fe4bc:      	fsubs	0x62c808
  4fe4c2:      	fildl	(%ebx)
  4fe4c4:      	movl	%ecx, 0x10(%esp)
  4fe4c8:      	leal	(%eax,%eax,2), %ecx
  4fe4cb:      	xorl	%eax, %eax
  4fe4cd:      	movl	%edi, 0x50(%esp)
  4fe4d1:      	fsubs	0x62c808
  4fe4d7:      	flds	0x62c808
  4fe4dd:      	fsubs	0x14(%esi,%eax)
  4fe4e1:      	flds	0x4(%esi,%eax)
  4fe4e5:      	faddl	0x632380
  4fe4eb:      	fxch	%st(1)
  4fe4ed:      	flds	0xc(%esi,%eax)
  4fe4f1:      	fmul	%st(3), %st
  4fe4f3:      	flds	0x10(%esi,%eax)
  4fe4f7:      	fmul	%st(5), %st
  4fe4f9:      	fxch	%st(3)
  4fe4fb:      	fstpl	0x38(%esp)
  4fe4ff:      	fxch	%st(1)
  4fe501:      	fmuls	0x62c810
  4fe507:      	fxch	%st(2)
  4fe509:      	fstps	0x10(%esi,%eax)
  4fe50d:      	fstps	0xc(%esi,%eax)
  4fe511:      	fstps	0x14(%esi,%eax)
  4fe515:      	movl	0x38(%esp), %edi
  4fe519:      	movl	%eax, 0x3e4(%esp,%eax)
  4fe520:      	movl	%eax, 0x114(%esp,%eax)
  4fe527:      	movl	%edi, 0x400(%esp,%eax)
  4fe52e:      	addl	$0x18, %eax
  4fe531:      	cmpl	%edx, %edi
  4fe533:      	jg	0x4fe539 <.text+0xfd539>
  4fe535:      	movl	%eax, %ebx
  4fe537:      	movl	%edi, %edx
  4fe539:      	cmpl	%ecx, %eax
  4fe53b:      	jne	0x4fe4d7 <.text+0xfd4d7>
  4fe53d:      	subl	$0x18, %ebx
  4fe540:      	leal	-0x18(%eax), %ecx
  4fe543:      	fcompp
  4fe545:      	movl	$0x0, 0x3e4(%esp,%eax)
  4fe550:      	movl	%ecx, 0xfc(%esp)
  4fe557:      	movl	0x8(%ebp), %edi
  4fe55a:      	movl	%ebx, 0xcc(%esp)
  4fe561:      	movl	%ebx, 0x9c(%esp)
  4fe568:      	movl	%ebx, 0xd0(%esp)
  4fe56f:      	movl	%esi, %ebp
  4fe571:      	movl	0x20(%edi), %eax
  4fe574:      	movl	(%edi), %ecx
  4fe576:      	addl	%edx, %eax
  4fe578:      	movl	0x14(%edi), %esi
  4fe57b:      	movl	0x1c(%edi), %edi
  4fe57e:      	imull	%ecx
  4fe580:      	addl	%edi, %esi
  4fe582:      	movl	%ecx, 0xc(%esp)
  4fe586:      	addl	%eax, %esi
  4fe588:      	movl	0x400(%esp,%ebx), %edi
  4fe58f:      	movl	%esi, 0x98(%esp)
  4fe596:      	movl	%ebx, 0xa0(%esp)
  4fe59d:      	movl	0xd0(%esp), %ecx
  4fe5a4:      	movl	0x400(%esp,%ecx), %eax
  4fe5ab:      	movl	%edi, 0x4(%esp)
  4fe5af:      	cmpl	%eax, %edi
  4fe5b1:      	jl	0x4fe6da <.text+0xfd6da>
  4fe5b7:      	movl	0x3fc(%esp,%ecx), %edx
  4fe5be:      	movl	%ecx, %eax
  4fe5c0:      	movl	%edx, 0xd0(%esp)
  4fe5c7:      	cmpl	0x9c(%esp), %edx
  4fe5ce:      	je	0x4fed4d <.text+0xfdd4d>
  4fe5d4:      	movl	0x400(%esp,%edx), %esi
  4fe5db:      	movl	%edx, %ecx
  4fe5dd:      	cmpl	%esi, %edi
  4fe5df:      	jge	0x4fe5b7 <.text+0xfd5b7>
  4fe5e1:      	flds	0x14(%ebp,%edx)
  4fe5e5:      	fsubs	0x14(%ebp,%eax)
  4fe5e9:      	flds	0x4(%ebp,%edx)
  4fe5ed:      	fsubs	0x4(%ebp,%eax)
  4fe5f1:      	flds	0x10(%ebp,%edx)
  4fe5f5:      	fsubs	0x10(%ebp,%eax)
  4fe5f9:      	fxch	%st(1)
  4fe5fb:      	fdivrs	0x62c808
  4fe601:      	flds	0xc(%ebp,%edx)
  4fe605:      	fsubs	0xc(%ebp,%eax)
  4fe609:      	fxch	%st(1)
  4fe60b:      	fmul	%st, %st(2)
  4fe60d:      	flds	0x8(%ebp,%edx)
  4fe611:      	fsubs	0x8(%ebp,%eax)
  4fe615:      	fxch	%st(2)
  4fe617:      	fmul	%st(1), %st
  4fe619:      	flds	(%ebp,%edx)
  4fe61d:      	fsubs	(%ebp,%eax)
  4fe621:      	fxch	%st(3)
  4fe623:      	fmul	%st(2), %st
  4fe625:      	fxch	%st(4)
  4fe627:      	fstps	0xec(%esp)
  4fe62e:      	fstps	0xe8(%esp)
  4fe635:      	fmul	%st, %st(3)
  4fe637:      	flds	0x4(%ebp,%eax)
  4fe63b:      	faddl	0x632380
  4fe641:      	fxch	%st(2)
  4fe643:      	fmulp	%st, %st(1)
  4fe645:      	fxch	%st(3)
  4fe647:      	fstps	0xf8(%esp)
  4fe64e:      	fstpl	0x38(%esp)
  4fe652:      	fstps	0xf4(%esp)
  4fe659:      	fildl	0x38(%esp)
  4fe65d:      	fxch	%st(1)
  4fe65f:      	fstps	0xf0(%esp)
  4fe666:      	fsubs	0x4(%ebp,%eax)
  4fe66a:      	flds	0xf0(%esp)
  4fe671:      	flds	0xf4(%esp)
  4fe678:      	fmul	%st(2), %st
  4fe67a:      	flds	0xe8(%esp)
  4fe681:      	fmul	%st(3), %st
  4fe683:      	flds	0xf8(%esp)
  4fe68a:      	fmul	%st(4), %st
  4fe68c:      	fxch	%st(2)
  4fe68e:      	fadds	0x8(%ebp,%eax)
  4fe692:      	flds	0xec(%esp)
  4fe699:      	fmul	%st(5), %st
  4fe69b:      	fxch	%st(2)
  4fe69d:      	fadds	0xc(%ebp,%eax)
  4fe6a1:      	fxch	%st(4)
  4fe6a3:      	fmulp	%st, %st(5)
  4fe6a5:      	fstps	0xd8(%esp)
  4fe6ac:      	fadds	0x10(%ebp,%eax)
  4fe6b0:      	fxch	%st(3)
  4fe6b2:      	fadds	(%ebp,%eax)
  4fe6b6:      	fxch	%st(2)
  4fe6b8:      	fstps	0xdc(%esp)
  4fe6bf:      	fadds	0x14(%ebp,%eax)
  4fe6c3:      	fxch	%st(2)
  4fe6c5:      	fstps	0xe0(%esp)
  4fe6cc:      	fstps	0xd4(%esp)
  4fe6d3:      	fstps	0xe4(%esp)
  4fe6da:      	movl	0xa0(%esp), %ecx
  4fe6e1:      	cmpl	0x400(%esp,%ecx), %edi
  4fe6e8:      	jl	0x4fe802 <.text+0xfd802>
  4fe6ee:      	movl	0xfc(%esp,%ecx), %edx
  4fe6f5:      	movl	%ecx, %eax
  4fe6f7:      	movl	%edx, 0xa0(%esp)
  4fe6fe:      	movl	%edx, %ecx
  4fe700:      	cmpl	0x400(%esp,%edx), %edi
  4fe707:      	jge	0x4fe6ee <.text+0xfd6ee>
  4fe709:      	flds	0x14(%ebp,%edx)
  4fe70d:      	fsubs	0x14(%ebp,%eax)
  4fe711:      	flds	0x4(%ebp,%edx)
  4fe715:      	fsubs	0x4(%ebp,%eax)
  4fe719:      	flds	0x10(%ebp,%edx)
  4fe71d:      	fsubs	0x10(%ebp,%eax)
  4fe721:      	fxch	%st(1)
  4fe723:      	fdivrs	0x62c808
  4fe729:      	flds	0xc(%ebp,%edx)
  4fe72d:      	fsubs	0xc(%ebp,%eax)
  4fe731:      	fxch	%st(1)
  4fe733:      	fmul	%st, %st(2)
  4fe735:      	flds	0x8(%ebp,%edx)
  4fe739:      	fsubs	0x8(%ebp,%eax)
  4fe73d:      	fxch	%st(2)
  4fe73f:      	fmul	%st(1), %st
  4fe741:      	flds	(%ebp,%edx)
  4fe745:      	fsubs	(%ebp,%eax)
  4fe749:      	fxch	%st(3)
  4fe74b:      	fmul	%st(2), %st
  4fe74d:      	fxch	%st(4)
  4fe74f:      	fstps	0xbc(%esp)
  4fe756:      	fstps	0xb8(%esp)
  4fe75d:      	fmul	%st, %st(3)
  4fe75f:      	flds	0x4(%ebp,%eax)
  4fe763:      	faddl	0x632380
  4fe769:      	fxch	%st(2)
  4fe76b:      	fmulp	%st, %st(1)
  4fe76d:      	fxch	%st(3)
  4fe76f:      	fstps	0xc8(%esp)
  4fe776:      	fstpl	0x38(%esp)
  4fe77a:      	fstps	0xc4(%esp)
  4fe781:      	fildl	0x38(%esp)
  4fe785:      	fxch	%st(1)
  4fe787:      	fstps	0xc0(%esp)
  4fe78e:      	fsubs	0x4(%ebp,%eax)
  4fe792:      	flds	0xc0(%esp)
  4fe799:      	flds	0xc4(%esp)
  4fe7a0:      	fmul	%st(2), %st
  4fe7a2:      	flds	0xb8(%esp)
  4fe7a9:      	fmul	%st(3), %st
  4fe7ab:      	flds	0xc8(%esp)
  4fe7b2:      	fmul	%st(4), %st
  4fe7b4:      	fxch	%st(2)
  4fe7b6:      	fadds	0x8(%ebp,%eax)
  4fe7ba:      	flds	0xbc(%esp)
  4fe7c1:      	fmul	%st(5), %st
  4fe7c3:      	fxch	%st(2)
  4fe7c5:      	fadds	0xc(%ebp,%eax)
  4fe7c9:      	fxch	%st(4)
  4fe7cb:      	fmulp	%st, %st(5)
  4fe7cd:      	fstps	0xa8(%esp)
  4fe7d4:      	fadds	0x10(%ebp,%eax)
  4fe7d8:      	fxch	%st(3)
  4fe7da:      	fadds	(%ebp,%eax)
  4fe7de:      	fxch	%st(2)
  4fe7e0:      	fstps	0xac(%esp)
  4fe7e7:      	fadds	0x14(%ebp,%eax)
  4fe7eb:      	fxch	%st(2)
  4fe7ed:      	fstps	0xb0(%esp)
  4fe7f4:      	fstps	0xa4(%esp)
  4fe7fb:      	fstps	0xb4(%esp)
  4fe802:      	flds	0xd4(%esp)
  4fe809:      	faddl	0x632380
  4fe80f:      	flds	0xa4(%esp)
  4fe816:      	faddl	0x632380
  4fe81c:      	fxch	%st(1)
  4fe81e:      	fstpl	0x48(%esp)
  4fe822:      	fstpl	0x40(%esp)
  4fe826:      	movl	0x48(%esp), %edx
  4fe82a:      	movl	0x40(%esp), %ebx
  4fe82e:      	cmpl	%edx, %ebx
  4fe830:      	je	0x4fec56 <.text+0xfdc56>
  4fe836:      	jl	0x4fe915 <.text+0xfd915>
  4fe83c:      	flds	0xb4(%esp)
  4fe843:      	fsubs	0xe4(%esp)
  4fe84a:      	flds	0xa4(%esp)
  4fe851:      	fsubs	0xd4(%esp)
  4fe858:      	flds	0xb0(%esp)
  4fe85f:      	fsubs	0xe0(%esp)
  4fe866:      	fxch	%st(1)
  4fe868:      	fdivrs	0x62c808
  4fe86e:      	flds	0xac(%esp)
  4fe875:      	fsubs	0xdc(%esp)
  4fe87c:      	fxch	%st(2)
  4fe87e:      	fmul	%st(1), %st
  4fe880:      	flds	0xa8(%esp)
  4fe887:      	fsubs	0xd8(%esp)
  4fe88e:      	fxch	%st(3)
  4fe890:      	fmul	%st(2), %st
  4fe892:      	fxch	%st(1)
  4fe894:      	fstps	0x1c(%esp)
  4fe898:      	fxch	%st(1)
  4fe89a:      	fmul	%st, %st(2)
  4fe89c:      	fxch	%st(1)
  4fe89e:      	fstps	0x18(%esp)
  4fe8a2:      	fmulp	%st, %st(2)
  4fe8a4:      	fildl	0x48(%esp)
  4fe8a8:      	fxch	%st(1)
  4fe8aa:      	fstps	0x20(%esp)
  4fe8ae:      	fsubs	0xd4(%esp)
  4fe8b5:      	fld	%st(1)
  4fe8b7:      	faddl	0x632380
  4fe8bd:      	fxch	%st(2)
  4fe8bf:      	fmul	%st(1), %st
  4fe8c1:      	flds	0x1c(%esp)
  4fe8c5:      	fxch	%st(3)
  4fe8c7:      	fstpl	0x68(%esp)
  4fe8cb:      	fadds	0xe4(%esp)
  4fe8d2:      	fxch	%st(2)
  4fe8d4:      	flds	0x18(%esp)
  4fe8d8:      	fmul	%st(2), %st
  4fe8da:      	fxch	%st(3)
  4fe8dc:      	faddl	0x632380
  4fe8e2:      	fxch	%st(3)
  4fe8e4:      	flds	0x20(%esp)
  4fe8e8:      	fmul	%st(3), %st
  4fe8ea:      	fxch	%st(4)
  4fe8ec:      	fstpl	0x90(%esp)
  4fe8f3:      	fadds	0xdc(%esp)
  4fe8fa:      	fxch	%st(2)
  4fe8fc:      	fmulp	%st, %st(1)
  4fe8fe:      	fxch	%st(2)
  4fe900:      	fadds	0xd8(%esp)
  4fe907:      	fxch	%st(2)
  4fe909:      	fadds	0xe0(%esp)
  4fe910:      	jmp	0x4fe9f3 <.text+0xfd9f3>
  4fe915:      	movl	%ebx, 0x48(%esp)
  4fe919:      	movl	%edx, %ebx
  4fe91b:      	movl	0x48(%esp), %edx
  4fe91f:      	flds	0xe4(%esp)
  4fe926:      	fsubs	0xb4(%esp)
  4fe92d:      	flds	0xd4(%esp)
  4fe934:      	fsubs	0xa4(%esp)
  4fe93b:      	flds	0xe0(%esp)
  4fe942:      	fsubs	0xb0(%esp)
  4fe949:      	fxch	%st(1)
  4fe94b:      	fdivrs	0x62c808
  4fe951:      	flds	0xdc(%esp)
  4fe958:      	fsubs	0xac(%esp)
  4fe95f:      	fxch	%st(2)
  4fe961:      	fmul	%st(1), %st
  4fe963:      	flds	0xd8(%esp)
  4fe96a:      	fsubs	0xa8(%esp)
  4fe971:      	fxch	%st(3)
  4fe973:      	fmul	%st(2), %st
  4fe975:      	fxch	%st(1)
  4fe977:      	fstps	0x1c(%esp)
  4fe97b:      	fxch	%st(1)
  4fe97d:      	fmul	%st, %st(2)
  4fe97f:      	fxch	%st(1)
  4fe981:      	fstps	0x18(%esp)
  4fe985:      	fmulp	%st, %st(2)
  4fe987:      	fildl	0x48(%esp)
  4fe98b:      	fxch	%st(1)
  4fe98d:      	fstps	0x20(%esp)
  4fe991:      	fsubs	0xa4(%esp)
  4fe998:      	fld	%st(1)
  4fe99a:      	faddl	0x632380
  4fe9a0:      	fxch	%st(2)
  4fe9a2:      	fmul	%st(1), %st
  4fe9a4:      	flds	0x1c(%esp)
  4fe9a8:      	fxch	%st(3)
  4fe9aa:      	fstpl	0x68(%esp)
  4fe9ae:      	fadds	0xb4(%esp)
  4fe9b5:      	fxch	%st(2)
  4fe9b7:      	flds	0x18(%esp)
  4fe9bb:      	fmul	%st(2), %st
  4fe9bd:      	fxch	%st(3)
  4fe9bf:      	faddl	0x632380
  4fe9c5:      	fxch	%st(3)
  4fe9c7:      	flds	0x20(%esp)
  4fe9cb:      	fmul	%st(3), %st
  4fe9cd:      	fxch	%st(4)
  4fe9cf:      	fstpl	0x90(%esp)
  4fe9d6:      	fadds	0xac(%esp)
  4fe9dd:      	fxch	%st(2)
  4fe9df:      	fmulp	%st, %st(1)
  4fe9e1:      	fxch	%st(2)
  4fe9e3:      	fadds	0xa8(%esp)
  4fe9ea:      	fxch	%st(2)
  4fe9ec:      	fadds	0xb0(%esp)
  4fe9f3:      	movl	0x68(%esp), %eax
  4fe9f7:      	movl	0x98(%esp), %edi
  4fe9fe:      	andl	$0xffff, %eax           # imm = 0xFFFF
  4fea03:      	subl	%edx, %ebx
  4fea05:      	orl	$0xfffe0000, %eax       # imm = 0xFFFE0000
  4fea0a:      	addl	%edx, %edi
  4fea0c:      	movl	%eax, 0x68(%esp)
  4fea10:      	flds	0x18(%esp)
  4fea14:      	fmuls	0x62c814
  4fea1a:      	flds	0x1c(%esp)
  4fea1e:      	fmuls	0x62c814
  4fea24:      	flds	0x20(%esp)
  4fea28:      	fmuls	0x62c814
  4fea2e:      	fxch	%st(2)
  4fea30:      	fstps	0x24(%esp)
  4fea34:      	fstps	0x28(%esp)
  4fea38:      	fstps	0x2c(%esp)
  4fea3c:      	fxch	%st(2)
  4fea3e:      	flds	0x62c80c
  4fea44:      	fdiv	%st(1), %st
  4fea46:      	fld	%st(3)
  4fea48:      	fmul	%st(1), %st
  4fea4a:      	fld	%st(3)
  4fea4c:      	fmulp	%st, %st(2)
  4fea4e:      	faddl	0x632380
  4fea54:      	fxch	%st(1)
  4fea56:      	faddl	0x632380
  4fea5c:      	fxch	%st(2)
  4fea5e:      	fadds	0x2c(%esp)
  4fea62:      	fxch	%st(1)
  4fea64:      	fstpl	0x78(%esp)
  4fea68:      	fxch	%st(1)
  4fea6a:      	fstpl	0x70(%esp)
  4fea6e:      	flds	0x62c80c
  4fea74:      	fdiv	%st(1), %st
  4fea76:      	decl	%ebx
  4fea77:      	jmp	0x4feb58 <.text+0xfdb58>
  4fea7c:      	flds	0x24(%esp)
  4fea80:      	faddp	%st, %st(3)
  4fea82:      	flds	0x28(%esp)
  4fea86:      	faddp	%st, %st(4)
  4fea88:      	fld	%st(2)
  4fea8a:      	fmul	%st(1), %st
  4fea8c:      	flds	0x2c(%esp)
  4fea90:      	fxch	%st(2)
  4fea92:      	fmul	%st(5), %st
  4fea94:      	fxch	%st(2)
  4fea96:      	faddp	%st, %st(3)
  4fea98:      	faddl	0x632380
  4fea9e:      	fxch	%st(1)
  4feaa0:      	faddl	0x632380
  4feaa6:      	fld	%st(2)
  4feaa8:      	fxch	%st(2)
  4feaaa:      	fstpl	0x80(%esp)
  4feab1:      	fstpl	0x88(%esp)
  4feab8:      	fdivrs	0x62c80c
  4feabe:      	movl	0x78(%esp), %ebp
  4feac2:      	movl	0x70(%esp), %esi
  4feac6:      	movl	0x88(%esp), %eax
  4feacd:      	movl	0x80(%esp), %edx
  4fead4:      	subl	%ebp, %eax
  4fead6:      	subl	%esi, %edx
  4fead8:      	sarl	$0x4, %eax
  4feadb:      	movl	%ebx, 0x8(%esp)
  4feadf:      	sarl	$0x4, %edx
  4feae2:      	movl	0x90(%esp), %ebx
  4feae9:      	movl	%edx, 0x58(%esp)
  4feaed:      	andl	$0xffff, %ebx           # imm = 0xFFFF
  4feaf3:      	movl	%eax, 0x60(%esp)
  4feaf7:      	orl	$0x1e0000, %ebx         # imm = 0x1E0000
  4feafd:      	movl	%ebp, %eax
  4feaff:      	movl	%esi, %edx
  4feb01:      	sarl	$0xb, %eax
  4feb04:      	movl	0x50(%esp), %ecx
  4feb08:      	sarl	$0x10, %edx
  4feb0b:      	andb	$-0x20, %al
  4feb0d:      	addl	%ecx, %eax
  4feb0f:      	movl	0x68(%esp), %ecx
  4feb13:      	addl	0x60(%esp), %ebp
  4feb17:      	addl	0x58(%esp), %esi
  4feb1b:      	movb	(%eax,%edx), %dl
  4feb1e:      	incl	%edi
  4feb1f:      	movb	%bh, %dh
  4feb21:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  4feb27:      	movb	0xd1e480(%edx), %al
  4feb2d:      	addl	%ecx, %ebx
  4feb2f:      	movb	%al, -0x1(%edi)
  4feb32:      	jge	0x4feafd <.text+0xfdafd>
  4feb34:      	movl	%ebx, 0x90(%esp)
  4feb3b:      	movl	0x8(%esp), %ebx
  4feb3f:      	movl	0x80(%esp), %eax
  4feb46:      	movl	0x88(%esp), %edx
  4feb4d:      	movl	%eax, 0x70(%esp)
  4feb51:      	movl	%edx, 0x78(%esp)
  4feb55:      	subl	$0x10, %ebx
  4feb58:      	cmpl	$0x10, %ebx
  4feb5b:      	jge	0x4fea7c <.text+0xfda7c>
  4feb61:      	movl	0x90(%esp), %eax
  4feb68:      	movl	%ebx, %ecx
  4feb6a:      	decl	%ebx
  4feb6b:      	movl	0x78(%esp), %ebp
  4feb6f:      	shll	$0x11, %ebx
  4feb72:      	andl	$0xffff, %eax           # imm = 0xFFFF
  4feb77:      	movl	0x70(%esp), %esi
  4feb7b:      	orl	%eax, %ebx
  4feb7d:      	cmpl	$0x0, %ecx
  4feb80:      	je	0x4fec34 <.text+0xfdc34>
  4feb86:      	fxch	%st(1)
  4feb88:      	fsubs	0x2c(%esp)
  4feb8c:      	flds	0x20(%esp)
  4feb90:      	fmuls	0x62c810(,%ecx,8)
  4feb97:      	flds	0x18(%esp)
  4feb9b:      	fmuls	0x62c810(,%ecx,8)
  4feba2:      	flds	0x1c(%esp)
  4feba6:      	fmuls	0x62c810(,%ecx,8)
  4febad:      	fxch	%st(2)
  4febaf:      	faddp	%st, %st(3)
  4febb1:      	faddp	%st, %st(4)
  4febb3:      	faddp	%st, %st(4)
  4febb5:      	fdivrs	0x62c80c
  4febbb:      	fmul	%st, %st(2)
  4febbd:      	fildl	0x70(%esp)
  4febc1:      	fxch	%st(1)
  4febc3:      	fmul	%st(4), %st
  4febc5:      	fildl	0x78(%esp)
  4febc9:      	fxch	%st(2)
  4febcb:      	fsubrp	%st, %st(4)
  4febcd:      	fsubp	%st, %st(1)
  4febcf:      	fxch	%st(2)
  4febd1:      	fmuls	0x62c814(,%ecx,8)
  4febd8:      	fxch	%st(2)
  4febda:      	fmuls	0x62c814(,%ecx,8)
  4febe1:      	fxch	%st(2)
  4febe3:      	faddl	0x632380
  4febe9:      	fxch	%st(2)
  4febeb:      	faddl	0x632380
  4febf1:      	fxch	%st(2)
  4febf3:      	fstl	0x58(%esp)
  4febf7:      	fxch	%st(2)
  4febf9:      	fstl	0x60(%esp)
  4febfd:      	movl	%ebp, %eax
  4febff:      	movl	%esi, %edx
  4fec01:      	sarl	$0xb, %eax
  4fec04:      	movl	0x50(%esp), %ecx
  4fec08:      	sarl	$0x10, %edx
  4fec0b:      	andb	$-0x20, %al
  4fec0d:      	addl	%ecx, %eax
  4fec0f:      	movl	0x68(%esp), %ecx
  4fec13:      	addl	0x60(%esp), %ebp
  4fec17:      	addl	0x58(%esp), %esi
  4fec1b:      	movb	(%eax,%edx), %dl
  4fec1e:      	incl	%edi
  4fec1f:      	movb	%bh, %dh
  4fec21:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  4fec27:      	movb	0xd1e480(%edx), %al
  4fec2d:      	addl	%ecx, %ebx
  4fec2f:      	movb	%al, -0x1(%edi)
  4fec32:      	jge	0x4febfd <.text+0xfdbfd>
  4fec34:      	sarl	$0xb, %ebp
  4fec37:      	xorl	%edx, %edx
  4fec39:      	sarl	$0x10, %esi
  4fec3c:      	movl	0x50(%esp), %eax
  4fec40:      	andl	$-0x20, %ebp
  4fec43:      	movb	%bh, %dh
  4fec45:      	addl	%ebp, %eax
  4fec47:      	fcompp
  4fec49:      	movb	(%eax,%esi), %dl
  4fec4c:      	fcompp
  4fec4e:      	movb	0xd1e480(%edx), %al
  4fec54:      	movb	%al, (%edi)
  4fec56:      	flds	0xb4(%esp)
  4fec5d:      	fadds	0xc8(%esp)
  4fec64:      	flds	0xa8(%esp)
  4fec6b:      	fadds	0xc4(%esp)
  4fec72:      	flds	0xb0(%esp)
  4fec79:      	fadds	0xbc(%esp)
  4fec80:      	flds	0xac(%esp)
  4fec87:      	fadds	0xb8(%esp)
  4fec8e:      	flds	0xa4(%esp)
  4fec95:      	fadds	0xc0(%esp)
  4fec9c:      	fxch	%st(3)
  4fec9e:      	fstps	0xa8(%esp)
  4feca5:      	fstps	0xac(%esp)
  4fecac:      	fstps	0xb0(%esp)
  4fecb3:      	fstps	0xa4(%esp)
  4fecba:      	fstps	0xb4(%esp)
  4fecc1:      	flds	0xe4(%esp)
  4fecc8:      	fadds	0xf8(%esp)
  4feccf:      	flds	0xd8(%esp)
  4fecd6:      	fadds	0xf4(%esp)
  4fecdd:      	flds	0xe0(%esp)
  4fece4:      	fadds	0xec(%esp)
  4feceb:      	flds	0xdc(%esp)
  4fecf2:      	fadds	0xe8(%esp)
  4fecf9:      	flds	0xd4(%esp)
  4fed00:      	fadds	0xf0(%esp)
  4fed07:      	fxch	%st(3)
  4fed09:      	fstps	0xd8(%esp)
  4fed10:      	fstps	0xdc(%esp)
  4fed17:      	fstps	0xe0(%esp)
  4fed1e:      	fstps	0xd4(%esp)
  4fed25:      	fstps	0xe4(%esp)
  4fed2c:      	movl	0x98(%esp), %esi
  4fed33:      	movl	0xc(%esp), %eax
  4fed37:      	movl	(%esp), %ebp
  4fed3a:      	addl	%eax, %esi
  4fed3c:      	movl	0x4(%esp), %edi
  4fed40:      	movl	%esi, 0x98(%esp)
  4fed47:      	incl	%edi
  4fed48:      	jmp	0x4fe59d <.text+0xfd59d>
  4fed4d:      	addl	$0x700, %esp            # imm = 0x700
  4fed53:      	popl	%ebp
  4fed54:      	popl	%edi
  4fed55:      	popl	%esi
  4fed56:      	popl	%ebx
  4fed57:      	popl	%ebp
  4fed58:      	retl
