; Entry: 004ff666
; Name: Terrain128PolyDouble
; Signature: void Terrain128PolyDouble(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
; Stop: 0x004fff35
; Reason: Exception while decompiling 004ff666: process: timeout 
; Command: C:\Program Files\LLVM\bin\llvm-objdump.EXE -d --no-show-raw-insn --start-address=0x004ff666 --stop-address=0x004fff35 C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe


C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe:	file format coff-i386

Disassembly of section .text:

00401000 <.text>:
  4ff666:      	pushl	%ebp
  4ff667:      	movl	%esp, %ebp
  4ff669:      	pushl	%ebx
  4ff66a:      	pushl	%esi
  4ff66b:      	pushl	%edi
  4ff66c:      	pushl	%ebp
  4ff66d:      	subl	$0x700, %esp            # imm = 0x700
  4ff673:      	movl	0x14(%ebp), %ebx
  4ff676:      	movl	$0x186a0, %edx          # imm = 0x186A0
  4ff67b:      	movl	0xc(%ebp), %esi
  4ff67e:      	movl	0x10(%ebp), %eax
  4ff681:      	fildl	0x4(%ebx)
  4ff684:      	movl	(%ebx), %ecx
  4ff686:      	movl	%esi, (%esp)
  4ff689:      	shll	$0x3, %eax
  4ff68c:      	leal	0x8(%ebx), %edi
  4ff68f:      	fildl	(%ebx)
  4ff691:      	movl	%ecx, 0x10(%esp)
  4ff695:      	leal	(%eax,%eax,2), %ecx
  4ff698:      	xorl	%eax, %eax
  4ff69a:      	movl	%edi, 0x50(%esp)
  4ff69e:      	flds	0x62c808
  4ff6a4:      	fsubs	0x14(%esi,%eax)
  4ff6a8:      	flds	0x4(%esi,%eax)
  4ff6ac:      	faddl	0x632380
  4ff6b2:      	fxch	%st(1)
  4ff6b4:      	flds	0xc(%esi,%eax)
  4ff6b8:      	fmul	%st(3), %st
  4ff6ba:      	flds	0x10(%esi,%eax)
  4ff6be:      	fmul	%st(5), %st
  4ff6c0:      	fxch	%st(3)
  4ff6c2:      	fstpl	0x38(%esp)
  4ff6c6:      	fxch	%st(1)
  4ff6c8:      	fmuls	0x62c810
  4ff6ce:      	fxch	%st(2)
  4ff6d0:      	fstps	0x10(%esi,%eax)
  4ff6d4:      	fstps	0xc(%esi,%eax)
  4ff6d8:      	fstps	0x14(%esi,%eax)
  4ff6dc:      	movl	0x38(%esp), %edi
  4ff6e0:      	movl	%eax, 0x3e4(%esp,%eax)
  4ff6e7:      	movl	%eax, 0x114(%esp,%eax)
  4ff6ee:      	movl	%edi, 0x400(%esp,%eax)
  4ff6f5:      	addl	$0x18, %eax
  4ff6f8:      	cmpl	%edx, %edi
  4ff6fa:      	jg	0x4ff700 <.text+0xfe700>
  4ff6fc:      	movl	%eax, %ebx
  4ff6fe:      	movl	%edi, %edx
  4ff700:      	cmpl	%ecx, %eax
  4ff702:      	jne	0x4ff69e <.text+0xfe69e>
  4ff704:      	subl	$0x18, %ebx
  4ff707:      	leal	-0x18(%eax), %ecx
  4ff70a:      	fcompp
  4ff70c:      	movl	$0x0, 0x3e4(%esp,%eax)
  4ff717:      	movl	%ecx, 0xfc(%esp)
  4ff71e:      	movl	0x8(%ebp), %edi
  4ff721:      	movl	%ebx, 0xcc(%esp)
  4ff728:      	movl	%ebx, 0x9c(%esp)
  4ff72f:      	movl	%ebx, 0xd0(%esp)
  4ff736:      	movl	%esi, %ebp
  4ff738:      	movl	0x20(%edi), %eax
  4ff73b:      	movl	(%edi), %ecx
  4ff73d:      	addl	%edx, %eax
  4ff73f:      	movl	0x14(%edi), %esi
  4ff742:      	movl	0x1c(%edi), %edi
  4ff745:      	imull	%ecx
  4ff747:      	addl	%edi, %esi
  4ff749:      	movl	%ecx, 0xc(%esp)
  4ff74d:      	addl	%eax, %esi
  4ff74f:      	movl	0x400(%esp,%ebx), %edi
  4ff756:      	movl	%esi, 0x98(%esp)
  4ff75d:      	movl	%ebx, 0xa0(%esp)
  4ff764:      	movl	0xd0(%esp), %ecx
  4ff76b:      	movl	0x400(%esp,%ecx), %eax
  4ff772:      	movl	%edi, 0x4(%esp)
  4ff776:      	cmpl	%eax, %edi
  4ff778:      	jl	0x4ff8a1 <.text+0xfe8a1>
  4ff77e:      	movl	0x3fc(%esp,%ecx), %edx
  4ff785:      	movl	%ecx, %eax
  4ff787:      	movl	%edx, 0xd0(%esp)
  4ff78e:      	cmpl	0x9c(%esp), %edx
  4ff795:      	je	0x4fff29 <.text+0xfef29>
  4ff79b:      	movl	0x400(%esp,%edx), %esi
  4ff7a2:      	movl	%edx, %ecx
  4ff7a4:      	cmpl	%esi, %edi
  4ff7a6:      	jge	0x4ff77e <.text+0xfe77e>
  4ff7a8:      	flds	0x14(%ebp,%edx)
  4ff7ac:      	fsubs	0x14(%ebp,%eax)
  4ff7b0:      	flds	0x4(%ebp,%edx)
  4ff7b4:      	fsubs	0x4(%ebp,%eax)
  4ff7b8:      	flds	0x10(%ebp,%edx)
  4ff7bc:      	fsubs	0x10(%ebp,%eax)
  4ff7c0:      	fxch	%st(1)
  4ff7c2:      	fdivrs	0x62c808
  4ff7c8:      	flds	0xc(%ebp,%edx)
  4ff7cc:      	fsubs	0xc(%ebp,%eax)
  4ff7d0:      	fxch	%st(1)
  4ff7d2:      	fmul	%st, %st(2)
  4ff7d4:      	flds	0x8(%ebp,%edx)
  4ff7d8:      	fsubs	0x8(%ebp,%eax)
  4ff7dc:      	fxch	%st(2)
  4ff7de:      	fmul	%st(1), %st
  4ff7e0:      	flds	(%ebp,%edx)
  4ff7e4:      	fsubs	(%ebp,%eax)
  4ff7e8:      	fxch	%st(3)
  4ff7ea:      	fmul	%st(2), %st
  4ff7ec:      	fxch	%st(4)
  4ff7ee:      	fstps	0xec(%esp)
  4ff7f5:      	fstps	0xe8(%esp)
  4ff7fc:      	fmul	%st, %st(3)
  4ff7fe:      	flds	0x4(%ebp,%eax)
  4ff802:      	faddl	0x632380
  4ff808:      	fxch	%st(2)
  4ff80a:      	fmulp	%st, %st(1)
  4ff80c:      	fxch	%st(3)
  4ff80e:      	fstps	0xf8(%esp)
  4ff815:      	fstpl	0x38(%esp)
  4ff819:      	fstps	0xf4(%esp)
  4ff820:      	fildl	0x38(%esp)
  4ff824:      	fxch	%st(1)
  4ff826:      	fstps	0xf0(%esp)
  4ff82d:      	fsubs	0x4(%ebp,%eax)
  4ff831:      	flds	0xf0(%esp)
  4ff838:      	flds	0xf4(%esp)
  4ff83f:      	fmul	%st(2), %st
  4ff841:      	flds	0xe8(%esp)
  4ff848:      	fmul	%st(3), %st
  4ff84a:      	flds	0xf8(%esp)
  4ff851:      	fmul	%st(4), %st
  4ff853:      	fxch	%st(2)
  4ff855:      	fadds	0x8(%ebp,%eax)
  4ff859:      	flds	0xec(%esp)
  4ff860:      	fmul	%st(5), %st
  4ff862:      	fxch	%st(2)
  4ff864:      	fadds	0xc(%ebp,%eax)
  4ff868:      	fxch	%st(4)
  4ff86a:      	fmulp	%st, %st(5)
  4ff86c:      	fstps	0xd8(%esp)
  4ff873:      	fadds	0x10(%ebp,%eax)
  4ff877:      	fxch	%st(3)
  4ff879:      	fadds	(%ebp,%eax)
  4ff87d:      	fxch	%st(2)
  4ff87f:      	fstps	0xdc(%esp)
  4ff886:      	fadds	0x14(%ebp,%eax)
  4ff88a:      	fxch	%st(2)
  4ff88c:      	fstps	0xe0(%esp)
  4ff893:      	fstps	0xd4(%esp)
  4ff89a:      	fstps	0xe4(%esp)
  4ff8a1:      	movl	0xa0(%esp), %ecx
  4ff8a8:      	cmpl	0x400(%esp,%ecx), %edi
  4ff8af:      	jl	0x4ff9c9 <.text+0xfe9c9>
  4ff8b5:      	movl	0xfc(%esp,%ecx), %edx
  4ff8bc:      	movl	%ecx, %eax
  4ff8be:      	movl	%edx, 0xa0(%esp)
  4ff8c5:      	movl	%edx, %ecx
  4ff8c7:      	cmpl	0x400(%esp,%edx), %edi
  4ff8ce:      	jge	0x4ff8b5 <.text+0xfe8b5>
  4ff8d0:      	flds	0x14(%ebp,%edx)
  4ff8d4:      	fsubs	0x14(%ebp,%eax)
  4ff8d8:      	flds	0x4(%ebp,%edx)
  4ff8dc:      	fsubs	0x4(%ebp,%eax)
  4ff8e0:      	flds	0x10(%ebp,%edx)
  4ff8e4:      	fsubs	0x10(%ebp,%eax)
  4ff8e8:      	fxch	%st(1)
  4ff8ea:      	fdivrs	0x62c808
  4ff8f0:      	flds	0xc(%ebp,%edx)
  4ff8f4:      	fsubs	0xc(%ebp,%eax)
  4ff8f8:      	fxch	%st(1)
  4ff8fa:      	fmul	%st, %st(2)
  4ff8fc:      	flds	0x8(%ebp,%edx)
  4ff900:      	fsubs	0x8(%ebp,%eax)
  4ff904:      	fxch	%st(2)
  4ff906:      	fmul	%st(1), %st
  4ff908:      	flds	(%ebp,%edx)
  4ff90c:      	fsubs	(%ebp,%eax)
  4ff910:      	fxch	%st(3)
  4ff912:      	fmul	%st(2), %st
  4ff914:      	fxch	%st(4)
  4ff916:      	fstps	0xbc(%esp)
  4ff91d:      	fstps	0xb8(%esp)
  4ff924:      	fmul	%st, %st(3)
  4ff926:      	flds	0x4(%ebp,%eax)
  4ff92a:      	faddl	0x632380
  4ff930:      	fxch	%st(2)
  4ff932:      	fmulp	%st, %st(1)
  4ff934:      	fxch	%st(3)
  4ff936:      	fstps	0xc8(%esp)
  4ff93d:      	fstpl	0x38(%esp)
  4ff941:      	fstps	0xc4(%esp)
  4ff948:      	fildl	0x38(%esp)
  4ff94c:      	fxch	%st(1)
  4ff94e:      	fstps	0xc0(%esp)
  4ff955:      	fsubs	0x4(%ebp,%eax)
  4ff959:      	flds	0xc0(%esp)
  4ff960:      	flds	0xc4(%esp)
  4ff967:      	fmul	%st(2), %st
  4ff969:      	flds	0xb8(%esp)
  4ff970:      	fmul	%st(3), %st
  4ff972:      	flds	0xc8(%esp)
  4ff979:      	fmul	%st(4), %st
  4ff97b:      	fxch	%st(2)
  4ff97d:      	fadds	0x8(%ebp,%eax)
  4ff981:      	flds	0xbc(%esp)
  4ff988:      	fmul	%st(5), %st
  4ff98a:      	fxch	%st(2)
  4ff98c:      	fadds	0xc(%ebp,%eax)
  4ff990:      	fxch	%st(4)
  4ff992:      	fmulp	%st, %st(5)
  4ff994:      	fstps	0xa8(%esp)
  4ff99b:      	fadds	0x10(%ebp,%eax)
  4ff99f:      	fxch	%st(3)
  4ff9a1:      	fadds	(%ebp,%eax)
  4ff9a5:      	fxch	%st(2)
  4ff9a7:      	fstps	0xac(%esp)
  4ff9ae:      	fadds	0x14(%ebp,%eax)
  4ff9b2:      	fxch	%st(2)
  4ff9b4:      	fstps	0xb0(%esp)
  4ff9bb:      	fstps	0xa4(%esp)
  4ff9c2:      	fstps	0xb4(%esp)
  4ff9c9:      	flds	0xd4(%esp)
  4ff9d0:      	faddl	0x632380
  4ff9d6:      	flds	0xa4(%esp)
  4ff9dd:      	faddl	0x632380
  4ff9e3:      	fxch	%st(1)
  4ff9e5:      	fstpl	0x48(%esp)
  4ff9e9:      	fstpl	0x40(%esp)
  4ff9ed:      	movl	0x48(%esp), %edx
  4ff9f1:      	movl	0x40(%esp), %ebx
  4ff9f5:      	cmpl	%edx, %ebx
  4ff9f7:      	je	0x4ffe32 <.text+0xfee32>
  4ff9fd:      	jl	0x4ffadc <.text+0xfeadc>
  4ffa03:      	flds	0xb4(%esp)
  4ffa0a:      	fsubs	0xe4(%esp)
  4ffa11:      	flds	0xa4(%esp)
  4ffa18:      	fsubs	0xd4(%esp)
  4ffa1f:      	flds	0xb0(%esp)
  4ffa26:      	fsubs	0xe0(%esp)
  4ffa2d:      	fxch	%st(1)
  4ffa2f:      	fdivrs	0x62c808
  4ffa35:      	flds	0xac(%esp)
  4ffa3c:      	fsubs	0xdc(%esp)
  4ffa43:      	fxch	%st(2)
  4ffa45:      	fmul	%st(1), %st
  4ffa47:      	flds	0xa8(%esp)
  4ffa4e:      	fsubs	0xd8(%esp)
  4ffa55:      	fxch	%st(3)
  4ffa57:      	fmul	%st(2), %st
  4ffa59:      	fxch	%st(1)
  4ffa5b:      	fstps	0x1c(%esp)
  4ffa5f:      	fxch	%st(1)
  4ffa61:      	fmul	%st, %st(2)
  4ffa63:      	fxch	%st(1)
  4ffa65:      	fstps	0x18(%esp)
  4ffa69:      	fmulp	%st, %st(2)
  4ffa6b:      	fildl	0x48(%esp)
  4ffa6f:      	fxch	%st(1)
  4ffa71:      	fstps	0x20(%esp)
  4ffa75:      	fsubs	0xd4(%esp)
  4ffa7c:      	fld	%st(1)
  4ffa7e:      	faddl	0x632380
  4ffa84:      	fxch	%st(2)
  4ffa86:      	fmul	%st(1), %st
  4ffa88:      	flds	0x1c(%esp)
  4ffa8c:      	fxch	%st(3)
  4ffa8e:      	fstpl	0x68(%esp)
  4ffa92:      	fadds	0xe4(%esp)
  4ffa99:      	fxch	%st(2)
  4ffa9b:      	flds	0x18(%esp)
  4ffa9f:      	fmul	%st(2), %st
  4ffaa1:      	fxch	%st(3)
  4ffaa3:      	faddl	0x632380
  4ffaa9:      	fxch	%st(3)
  4ffaab:      	flds	0x20(%esp)
  4ffaaf:      	fmul	%st(3), %st
  4ffab1:      	fxch	%st(4)
  4ffab3:      	fstpl	0x90(%esp)
  4ffaba:      	fadds	0xdc(%esp)
  4ffac1:      	fxch	%st(2)
  4ffac3:      	fmulp	%st, %st(1)
  4ffac5:      	fxch	%st(2)
  4ffac7:      	fadds	0xd8(%esp)
  4fface:      	fxch	%st(2)
  4ffad0:      	fadds	0xe0(%esp)
  4ffad7:      	jmp	0x4ffbba <.text+0xfebba>
  4ffadc:      	movl	%ebx, 0x48(%esp)
  4ffae0:      	movl	%edx, %ebx
  4ffae2:      	movl	0x48(%esp), %edx
  4ffae6:      	flds	0xe4(%esp)
  4ffaed:      	fsubs	0xb4(%esp)
  4ffaf4:      	flds	0xd4(%esp)
  4ffafb:      	fsubs	0xa4(%esp)
  4ffb02:      	flds	0xe0(%esp)
  4ffb09:      	fsubs	0xb0(%esp)
  4ffb10:      	fxch	%st(1)
  4ffb12:      	fdivrs	0x62c808
  4ffb18:      	flds	0xdc(%esp)
  4ffb1f:      	fsubs	0xac(%esp)
  4ffb26:      	fxch	%st(2)
  4ffb28:      	fmul	%st(1), %st
  4ffb2a:      	flds	0xd8(%esp)
  4ffb31:      	fsubs	0xa8(%esp)
  4ffb38:      	fxch	%st(3)
  4ffb3a:      	fmul	%st(2), %st
  4ffb3c:      	fxch	%st(1)
  4ffb3e:      	fstps	0x1c(%esp)
  4ffb42:      	fxch	%st(1)
  4ffb44:      	fmul	%st, %st(2)
  4ffb46:      	fxch	%st(1)
  4ffb48:      	fstps	0x18(%esp)
  4ffb4c:      	fmulp	%st, %st(2)
  4ffb4e:      	fildl	0x48(%esp)
  4ffb52:      	fxch	%st(1)
  4ffb54:      	fstps	0x20(%esp)
  4ffb58:      	fsubs	0xa4(%esp)
  4ffb5f:      	fld	%st(1)
  4ffb61:      	faddl	0x632380
  4ffb67:      	fxch	%st(2)
  4ffb69:      	fmul	%st(1), %st
  4ffb6b:      	flds	0x1c(%esp)
  4ffb6f:      	fxch	%st(3)
  4ffb71:      	fstpl	0x68(%esp)
  4ffb75:      	fadds	0xb4(%esp)
  4ffb7c:      	fxch	%st(2)
  4ffb7e:      	flds	0x18(%esp)
  4ffb82:      	fmul	%st(2), %st
  4ffb84:      	fxch	%st(3)
  4ffb86:      	faddl	0x632380
  4ffb8c:      	fxch	%st(3)
  4ffb8e:      	flds	0x20(%esp)
  4ffb92:      	fmul	%st(3), %st
  4ffb94:      	fxch	%st(4)
  4ffb96:      	fstpl	0x90(%esp)
  4ffb9d:      	fadds	0xac(%esp)
  4ffba4:      	fxch	%st(2)
  4ffba6:      	fmulp	%st, %st(1)
  4ffba8:      	fxch	%st(2)
  4ffbaa:      	fadds	0xa8(%esp)
  4ffbb1:      	fxch	%st(2)
  4ffbb3:      	fadds	0xb0(%esp)
  4ffbba:      	movl	0x68(%esp), %eax
  4ffbbe:      	movl	0x98(%esp), %edi
  4ffbc5:      	andl	$0xffff, %eax           # imm = 0xFFFF
  4ffbca:      	subl	%edx, %ebx
  4ffbcc:      	orl	$0xfffe0000, %eax       # imm = 0xFFFE0000
  4ffbd1:      	addl	%edx, %edi
  4ffbd3:      	movl	%eax, 0x68(%esp)
  4ffbd7:      	flds	0x18(%esp)
  4ffbdb:      	fmuls	0x62c814
  4ffbe1:      	flds	0x1c(%esp)
  4ffbe5:      	fmuls	0x62c814
  4ffbeb:      	flds	0x20(%esp)
  4ffbef:      	fmuls	0x62c814
  4ffbf5:      	fxch	%st(2)
  4ffbf7:      	fstps	0x24(%esp)
  4ffbfb:      	fstps	0x28(%esp)
  4ffbff:      	fstps	0x2c(%esp)
  4ffc03:      	fxch	%st(2)
  4ffc05:      	flds	0x62c80c
  4ffc0b:      	fdiv	%st(1), %st
  4ffc0d:      	fld	%st(3)
  4ffc0f:      	fmul	%st(1), %st
  4ffc11:      	fld	%st(3)
  4ffc13:      	fmulp	%st, %st(2)
  4ffc15:      	faddl	0x632380
  4ffc1b:      	fxch	%st(1)
  4ffc1d:      	faddl	0x632380
  4ffc23:      	fxch	%st(2)
  4ffc25:      	fadds	0x2c(%esp)
  4ffc29:      	fxch	%st(1)
  4ffc2b:      	fstpl	0x78(%esp)
  4ffc2f:      	fxch	%st(1)
  4ffc31:      	fstpl	0x70(%esp)
  4ffc35:      	flds	0x62c80c
  4ffc3b:      	fdiv	%st(1), %st
  4ffc3d:      	decl	%ebx
  4ffc3e:      	jmp	0x4ffd34 <.text+0xfed34>
  4ffc43:      	flds	0x24(%esp)
  4ffc47:      	faddp	%st, %st(3)
  4ffc49:      	flds	0x28(%esp)
  4ffc4d:      	faddp	%st, %st(4)
  4ffc4f:      	fld	%st(2)
  4ffc51:      	fmul	%st(1), %st
  4ffc53:      	flds	0x2c(%esp)
  4ffc57:      	fxch	%st(2)
  4ffc59:      	fmul	%st(5), %st
  4ffc5b:      	fxch	%st(2)
  4ffc5d:      	faddp	%st, %st(3)
  4ffc5f:      	faddl	0x632380
  4ffc65:      	fxch	%st(1)
  4ffc67:      	faddl	0x632380
  4ffc6d:      	fld	%st(2)
  4ffc6f:      	fxch	%st(2)
  4ffc71:      	fstpl	0x80(%esp)
  4ffc78:      	fstpl	0x88(%esp)
  4ffc7f:      	fdivrs	0x62c80c
  4ffc85:      	movl	0x78(%esp), %ebp
  4ffc89:      	movl	0x70(%esp), %esi
  4ffc8d:      	movl	0x88(%esp), %eax
  4ffc94:      	movl	0x80(%esp), %edx
  4ffc9b:      	subl	%ebp, %eax
  4ffc9d:      	subl	%esi, %edx
  4ffc9f:      	sarl	$0x4, %eax
  4ffca2:      	movl	%ebx, 0x8(%esp)
  4ffca6:      	sarl	$0x4, %edx
  4ffca9:      	movl	0x90(%esp), %ebx
  4ffcb0:      	movl	%edx, 0x58(%esp)
  4ffcb4:      	andl	$0xffff, %ebx           # imm = 0xFFFF
  4ffcba:      	movl	%eax, 0x60(%esp)
  4ffcbe:      	orl	$0x1e0000, %ebx         # imm = 0x1E0000
  4ffcc4:      	movl	%ebp, %eax
  4ffcc6:      	movl	%esi, %edx
  4ffcc8:      	sarl	$0x9, %eax
  4ffccb:      	movl	0x50(%esp), %ecx
  4ffccf:      	sarl	$0x10, %edx
  4ffcd2:      	andb	$-0x80, %al
  4ffcd4:      	addl	0x60(%esp), %ebp
  4ffcd8:      	addl	0x58(%esp), %esi
  4ffcdc:      	addl	%ecx, %eax
  4ffcde:      	movl	0x68(%esp), %ecx
  4ffce2:      	addl	0x60(%esp), %ebp
  4ffce6:      	addl	0x58(%esp), %esi
  4ffcea:      	movb	(%eax,%edx), %dl
  4ffced:      	addl	$0x2, %edi
  4ffcf0:      	movb	%bh, %dh
  4ffcf2:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  4ffcf8:      	movb	0xd1e480(%edx), %al
  4ffcfe:      	addl	%ecx, %ebx
  4ffd00:      	movb	%al, %ah
  4ffd02:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  4ffd08:      	movw	%ax, -0x2(%edi)
  4ffd0c:      	addl	%ecx, %ebx
  4ffd0e:      	jge	0x4ffcc4 <.text+0xfecc4>
  4ffd10:      	movl	%ebx, 0x90(%esp)
  4ffd17:      	movl	0x8(%esp), %ebx
  4ffd1b:      	movl	0x80(%esp), %eax
  4ffd22:      	movl	0x88(%esp), %edx
  4ffd29:      	movl	%eax, 0x70(%esp)
  4ffd2d:      	movl	%edx, 0x78(%esp)
  4ffd31:      	subl	$0x10, %ebx
  4ffd34:      	cmpl	$0x10, %ebx
  4ffd37:      	jge	0x4ffc43 <.text+0xfec43>
  4ffd3d:      	movl	0x90(%esp), %eax
  4ffd44:      	movl	%ebx, %ecx
  4ffd46:      	decl	%ebx
  4ffd47:      	movl	0x78(%esp), %ebp
  4ffd4b:      	shll	$0x11, %ebx
  4ffd4e:      	andl	$0xffff, %eax           # imm = 0xFFFF
  4ffd53:      	movl	0x70(%esp), %esi
  4ffd57:      	orl	%eax, %ebx
  4ffd59:      	cmpl	$0x0, %ecx
  4ffd5c:      	je	0x4ffe10 <.text+0xfee10>
  4ffd62:      	fxch	%st(1)
  4ffd64:      	fsubs	0x2c(%esp)
  4ffd68:      	flds	0x20(%esp)
  4ffd6c:      	fmuls	0x62c810(,%ecx,8)
  4ffd73:      	flds	0x18(%esp)
  4ffd77:      	fmuls	0x62c810(,%ecx,8)
  4ffd7e:      	flds	0x1c(%esp)
  4ffd82:      	fmuls	0x62c810(,%ecx,8)
  4ffd89:      	fxch	%st(2)
  4ffd8b:      	faddp	%st, %st(3)
  4ffd8d:      	faddp	%st, %st(4)
  4ffd8f:      	faddp	%st, %st(4)
  4ffd91:      	fdivrs	0x62c80c
  4ffd97:      	fmul	%st, %st(2)
  4ffd99:      	fildl	0x70(%esp)
  4ffd9d:      	fxch	%st(1)
  4ffd9f:      	fmul	%st(4), %st
  4ffda1:      	fildl	0x78(%esp)
  4ffda5:      	fxch	%st(2)
  4ffda7:      	fsubrp	%st, %st(4)
  4ffda9:      	fsubp	%st, %st(1)
  4ffdab:      	fxch	%st(2)
  4ffdad:      	fmuls	0x62c814(,%ecx,8)
  4ffdb4:      	fxch	%st(2)
  4ffdb6:      	fmuls	0x62c814(,%ecx,8)
  4ffdbd:      	fxch	%st(2)
  4ffdbf:      	faddl	0x632380
  4ffdc5:      	fxch	%st(2)
  4ffdc7:      	faddl	0x632380
  4ffdcd:      	fxch	%st(2)
  4ffdcf:      	fstl	0x58(%esp)
  4ffdd3:      	fxch	%st(2)
  4ffdd5:      	fstl	0x60(%esp)
  4ffdd9:      	movl	%ebp, %eax
  4ffddb:      	movl	%esi, %edx
  4ffddd:      	sarl	$0x9, %eax
  4ffde0:      	movl	0x50(%esp), %ecx
  4ffde4:      	sarl	$0x10, %edx
  4ffde7:      	andb	$-0x80, %al
  4ffde9:      	addl	%ecx, %eax
  4ffdeb:      	movl	0x68(%esp), %ecx
  4ffdef:      	addl	0x60(%esp), %ebp
  4ffdf3:      	addl	0x58(%esp), %esi
  4ffdf7:      	movb	(%eax,%edx), %dl
  4ffdfa:      	incl	%edi
  4ffdfb:      	movb	%bh, %dh
  4ffdfd:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  4ffe03:      	movb	0xd1e480(%edx), %al
  4ffe09:      	addl	%ecx, %ebx
  4ffe0b:      	movb	%al, -0x1(%edi)
  4ffe0e:      	jge	0x4ffdd9 <.text+0xfedd9>
  4ffe10:      	sarl	$0x9, %ebp
  4ffe13:      	xorl	%edx, %edx
  4ffe15:      	sarl	$0x10, %esi
  4ffe18:      	movl	0x50(%esp), %eax
  4ffe1c:      	andl	$-0x80, %ebp
  4ffe1f:      	movb	%bh, %dh
  4ffe21:      	addl	%ebp, %eax
  4ffe23:      	fcompp
  4ffe25:      	movb	(%eax,%esi), %dl
  4ffe28:      	fcompp
  4ffe2a:      	movb	0xd1e480(%edx), %al
  4ffe30:      	movb	%al, (%edi)
  4ffe32:      	flds	0xb4(%esp)
  4ffe39:      	fadds	0xc8(%esp)
  4ffe40:      	flds	0xa8(%esp)
  4ffe47:      	fadds	0xc4(%esp)
  4ffe4e:      	flds	0xb0(%esp)
  4ffe55:      	fadds	0xbc(%esp)
  4ffe5c:      	flds	0xac(%esp)
  4ffe63:      	fadds	0xb8(%esp)
  4ffe6a:      	flds	0xa4(%esp)
  4ffe71:      	fadds	0xc0(%esp)
  4ffe78:      	fxch	%st(3)
  4ffe7a:      	fstps	0xa8(%esp)
  4ffe81:      	fstps	0xac(%esp)
  4ffe88:      	fstps	0xb0(%esp)
  4ffe8f:      	fstps	0xa4(%esp)
  4ffe96:      	fstps	0xb4(%esp)
  4ffe9d:      	flds	0xe4(%esp)
  4ffea4:      	fadds	0xf8(%esp)
  4ffeab:      	flds	0xd8(%esp)
  4ffeb2:      	fadds	0xf4(%esp)
  4ffeb9:      	flds	0xe0(%esp)
  4ffec0:      	fadds	0xec(%esp)
  4ffec7:      	flds	0xdc(%esp)
  4ffece:      	fadds	0xe8(%esp)
  4ffed5:      	flds	0xd4(%esp)
  4ffedc:      	fadds	0xf0(%esp)
  4ffee3:      	fxch	%st(3)
  4ffee5:      	fstps	0xd8(%esp)
  4ffeec:      	fstps	0xdc(%esp)
  4ffef3:      	fstps	0xe0(%esp)
  4ffefa:      	fstps	0xd4(%esp)
  4fff01:      	fstps	0xe4(%esp)
  4fff08:      	movl	0x98(%esp), %esi
  4fff0f:      	movl	0xc(%esp), %eax
  4fff13:      	movl	(%esp), %ebp
  4fff16:      	addl	%eax, %esi
  4fff18:      	movl	0x4(%esp), %edi
  4fff1c:      	movl	%esi, 0x98(%esp)
  4fff23:      	incl	%edi
  4fff24:      	jmp	0x4ff764 <.text+0xfe764>
  4fff29:      	addl	$0x700, %esp            # imm = 0x700
  4fff2f:      	popl	%ebp
  4fff30:      	popl	%edi
  4fff31:      	popl	%esi
  4fff32:      	popl	%ebx
  4fff33:      	popl	%ebp
  4fff34:      	retl
