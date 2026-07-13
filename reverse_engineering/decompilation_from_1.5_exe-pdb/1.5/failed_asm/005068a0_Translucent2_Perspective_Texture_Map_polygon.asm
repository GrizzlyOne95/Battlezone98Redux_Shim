; Entry: 005068a0
; Name: Translucent2_Perspective_Texture_Map_polygon
; Signature: void Translucent2_Perspective_Texture_Map_polygon(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
; Stop: 0x005070ea
; Reason: Exception while decompiling 005068a0: process: timeout 
; Command: C:\Program Files\LLVM\bin\llvm-objdump.EXE -d --no-show-raw-insn --start-address=0x005068a0 --stop-address=0x005070ea C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe


C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe:	file format coff-i386

Disassembly of section .text:

00401000 <.text>:
  5068a0:      	pushl	%ebp
  5068a1:      	movl	%esp, %ebp
  5068a3:      	pushl	%ebx
  5068a4:      	pushl	%esi
  5068a5:      	pushl	%edi
  5068a6:      	movl	0x14(%ebp), %ebx
  5068a9:      	pushl	%ebp
  5068aa:      	movl	0xcfdbc0, %eax
  5068af:      	subl	$0x7d8, %esp            # imm = 0x7D8
  5068b5:      	leal	0x6d8(%esp), %ecx
  5068bc:      	calll	0x50550a <.text+0x10450a>
  5068c1:      	cmpl	%ebx, %eax
  5068c3:      	je	0x506933 <.text+0x105933>
  5068c5:      	movl	%ebx, 0xcfdbc0
  5068cb:      	leal	0xcfdbd8, %edx
  5068d1:      	movl	(%ebx), %eax
  5068d3:      	movl	0x4(%ebx), %ecx
  5068d6:      	leal	0x8(%ebx), %esi
  5068d9:      	movl	%ecx, 0x4(%esp)
  5068dd:      	movl	%eax, %edi
  5068df:      	addl	$0x3, %ecx
  5068e2:      	addl	%esi, %edi
  5068e4:      	leal	(%esi,%eax,2), %ebx
  5068e7:      	leal	(%eax,%eax,2), %eax
  5068ea:      	movl	%esi, -0x4(%edx)
  5068ed:      	movl	%esi, -0x8(%edx)
  5068f0:      	movl	%esi, -0xc(%edx)
  5068f3:      	movl	%esi, -0x10(%edx)
  5068f6:      	movl	%esi, (%edx)
  5068f8:      	movl	%edi, 0x4(%edx)
  5068fb:      	movl	%ebx, 0x8(%edx)
  5068fe:      	addl	%eax, %esi
  506900:      	addl	%eax, %edi
  506902:      	addl	%eax, %ebx
  506904:      	addl	$0xc, %edx
  506907:      	subl	$0x3, %ecx
  50690a:      	jge	0x5068f6 <.text+0x1058f6>
  50690c:      	movl	0x4(%esp), %edx
  506910:      	movl	0xcfdbd4(,%edx,4), %eax
  506917:      	movl	%eax, 0xcfdbd8(,%edx,4)
  50691e:      	movl	%eax, 0xcfdbdc(,%edx,4)
  506925:      	movl	%eax, 0xcfdbe0(,%edx,4)
  50692c:      	movl	%eax, 0xcfdbe4(,%edx,4)
  506933:      	movl	0x14(%ebp), %ebx
  506936:      	movl	$0x186a0, %edx          # imm = 0x186A0
  50693b:      	movl	0xc(%ebp), %esi
  50693e:      	movl	0x10(%ebp), %eax
  506941:      	fildl	0x4(%ebx)
  506944:      	movl	(%ebx), %ecx
  506946:      	movl	%esi, (%esp)
  506949:      	shll	$0x3, %eax
  50694c:      	leal	0x8(%ebx), %edi
  50694f:      	fsubs	0x62c808
  506955:      	fildl	(%ebx)
  506957:      	movl	%ecx, 0x10(%esp)
  50695b:      	leal	(%eax,%eax,2), %ecx
  50695e:      	xorl	%eax, %eax
  506960:      	movl	%edi, 0x1c(%esp)
  506964:      	fsubs	0x62c808
  50696a:      	flds	0x4(%esi,%eax)
  50696e:      	faddl	0x632380
  506974:      	flds	0xc(%esi,%eax)
  506978:      	fmul	%st(2), %st
  50697a:      	flds	0x10(%esi,%eax)
  50697e:      	fmul	%st(4), %st
  506980:      	fxch	%st(2)
  506982:      	fstpl	0x640(%esp)
  506989:      	fstps	0xc(%esi,%eax)
  50698d:      	fstps	0x10(%esi,%eax)
  506991:      	movl	0x640(%esp), %edi
  506998:      	movl	%eax, 0x320(%esp,%eax)
  50699f:      	movl	%eax, 0x50(%esp,%eax)
  5069a3:      	movl	%edi, 0x33c(%esp,%eax)
  5069aa:      	addl	$0x18, %eax
  5069ad:      	cmpl	%edx, %edi
  5069af:      	jg	0x5069b5 <.text+0x1059b5>
  5069b1:      	movl	%eax, %ebx
  5069b3:      	movl	%edi, %edx
  5069b5:      	cmpl	%ecx, %eax
  5069b7:      	jne	0x50696a <.text+0x10596a>
  5069b9:      	subl	$0x18, %ebx
  5069bc:      	leal	-0x18(%eax), %ecx
  5069bf:      	fcompp
  5069c1:      	movl	$0x0, 0x320(%esp,%eax)
  5069cc:      	movl	%ecx, 0x38(%esp)
  5069d0:      	movl	0x8(%ebp), %edi
  5069d3:      	movl	%ebx, 0x6b0(%esp)
  5069da:      	movl	%ebx, 0x688(%esp)
  5069e1:      	movl	%ebx, 0x6b4(%esp)
  5069e8:      	movl	%esi, %ebp
  5069ea:      	movl	0x20(%edi), %eax
  5069ed:      	movl	(%edi), %ecx
  5069ef:      	addl	%edx, %eax
  5069f1:      	movl	0x14(%edi), %esi
  5069f4:      	movl	0x1c(%edi), %edi
  5069f7:      	imull	%ecx
  5069f9:      	addl	%edi, %esi
  5069fb:      	movl	%ecx, 0xc(%esp)
  5069ff:      	addl	%eax, %esi
  506a01:      	movl	0x33c(%esp,%ebx), %edi
  506a08:      	movl	%esi, 0x18(%esp)
  506a0c:      	movl	%ebx, 0x68c(%esp)
  506a13:      	movl	0x6b4(%esp), %ecx
  506a1a:      	movl	0x33c(%esp,%ecx), %eax
  506a21:      	movl	%edi, 0x4(%esp)
  506a25:      	cmpl	%eax, %edi
  506a27:      	jl	0x506b31 <.text+0x105b31>
  506a2d:      	movl	0x338(%esp,%ecx), %edx
  506a34:      	movl	%ecx, %eax
  506a36:      	movl	%edx, 0x6b4(%esp)
  506a3d:      	cmpl	0x688(%esp), %edx
  506a44:      	je	0x5070d2 <.text+0x1060d2>
  506a4a:      	movl	0x33c(%esp,%edx), %esi
  506a51:      	movl	%edx, %ecx
  506a53:      	cmpl	%esi, %edi
  506a55:      	jge	0x506a2d <.text+0x105a2d>
  506a57:      	flds	0x4(%ebp,%edx)
  506a5b:      	fsubs	0x4(%ebp,%eax)
  506a5f:      	flds	0x10(%ebp,%edx)
  506a63:      	fsubs	0x10(%ebp,%eax)
  506a67:      	fxch	%st(1)
  506a69:      	fdivrs	0x62c808
  506a6f:      	flds	0xc(%ebp,%edx)
  506a73:      	fsubs	0xc(%ebp,%eax)
  506a77:      	fxch	%st(1)
  506a79:      	fmul	%st, %st(2)
  506a7b:      	flds	0x8(%ebp,%edx)
  506a7f:      	fsubs	0x8(%ebp,%eax)
  506a83:      	fxch	%st(2)
  506a85:      	fmul	%st(1), %st
  506a87:      	flds	(%ebp,%edx)
  506a8b:      	fsubs	(%ebp,%eax)
  506a8f:      	fxch	%st(3)
  506a91:      	fmul	%st(2), %st
  506a93:      	fxch	%st(4)
  506a95:      	fstps	0x6cc(%esp)
  506a9c:      	flds	0x4(%ebp,%eax)
  506aa0:      	faddl	0x632380
  506aa6:      	fxch	%st(3)
  506aa8:      	fmulp	%st, %st(2)
  506aaa:      	fstps	0x6c8(%esp)
  506ab1:      	fxch	%st(1)
  506ab3:      	fstpl	0x640(%esp)
  506aba:      	fstps	0x6d0(%esp)
  506ac1:      	fildl	0x640(%esp)
  506ac8:      	fxch	%st(1)
  506aca:      	fstps	0x6d4(%esp)
  506ad1:      	fsubs	0x4(%ebp,%eax)
  506ad5:      	flds	0x6d0(%esp)
  506adc:      	flds	0x6d4(%esp)
  506ae3:      	fmul	%st(2), %st
  506ae5:      	flds	0x6c8(%esp)
  506aec:      	fmul	%st(3), %st
  506aee:      	fxch	%st(1)
  506af0:      	fadds	0x8(%ebp,%eax)
  506af4:      	flds	0x6cc(%esp)
  506afb:      	fmul	%st(4), %st
  506afd:      	fxch	%st(2)
  506aff:      	fadds	0xc(%ebp,%eax)
  506b03:      	fxch	%st(3)
  506b05:      	fmulp	%st, %st(4)
  506b07:      	fstps	0x6bc(%esp)
  506b0e:      	fadds	0x10(%ebp,%eax)
  506b12:      	fxch	%st(2)
  506b14:      	fadds	(%ebp,%eax)
  506b18:      	fxch	%st(1)
  506b1a:      	fstps	0x6c0(%esp)
  506b21:      	fxch	%st(1)
  506b23:      	fstps	0x6c4(%esp)
  506b2a:      	fstps	0x6b8(%esp)
  506b31:      	movl	0x68c(%esp), %ecx
  506b38:      	cmpl	0x33c(%esp,%ecx), %edi
  506b3f:      	jl	0x506c37 <.text+0x105c37>
  506b45:      	movl	0x38(%esp,%ecx), %edx
  506b49:      	movl	%ecx, %eax
  506b4b:      	movl	%edx, 0x68c(%esp)
  506b52:      	movl	%edx, %ecx
  506b54:      	cmpl	0x33c(%esp,%edx), %edi
  506b5b:      	jge	0x506b45 <.text+0x105b45>
  506b5d:      	flds	0x4(%ebp,%edx)
  506b61:      	fsubs	0x4(%ebp,%eax)
  506b65:      	flds	0x10(%ebp,%edx)
  506b69:      	fsubs	0x10(%ebp,%eax)
  506b6d:      	fxch	%st(1)
  506b6f:      	fdivrs	0x62c808
  506b75:      	flds	0xc(%ebp,%edx)
  506b79:      	fsubs	0xc(%ebp,%eax)
  506b7d:      	fxch	%st(1)
  506b7f:      	fmul	%st, %st(2)
  506b81:      	flds	0x8(%ebp,%edx)
  506b85:      	fsubs	0x8(%ebp,%eax)
  506b89:      	fxch	%st(2)
  506b8b:      	fmul	%st(1), %st
  506b8d:      	flds	(%ebp,%edx)
  506b91:      	fsubs	(%ebp,%eax)
  506b95:      	fxch	%st(3)
  506b97:      	fmul	%st(2), %st
  506b99:      	fxch	%st(4)
  506b9b:      	fstps	0x6a4(%esp)
  506ba2:      	flds	0x4(%ebp,%eax)
  506ba6:      	faddl	0x632380
  506bac:      	fxch	%st(3)
  506bae:      	fmulp	%st, %st(2)
  506bb0:      	fstps	0x6a0(%esp)
  506bb7:      	fxch	%st(1)
  506bb9:      	fstpl	0x640(%esp)
  506bc0:      	fstps	0x6a8(%esp)
  506bc7:      	fildl	0x640(%esp)
  506bce:      	fxch	%st(1)
  506bd0:      	fstps	0x6ac(%esp)
  506bd7:      	fsubs	0x4(%ebp,%eax)
  506bdb:      	flds	0x6a8(%esp)
  506be2:      	flds	0x6ac(%esp)
  506be9:      	fmul	%st(2), %st
  506beb:      	flds	0x6a0(%esp)
  506bf2:      	fmul	%st(3), %st
  506bf4:      	fxch	%st(1)
  506bf6:      	fadds	0x8(%ebp,%eax)
  506bfa:      	flds	0x6a4(%esp)
  506c01:      	fmul	%st(4), %st
  506c03:      	fxch	%st(2)
  506c05:      	fadds	0xc(%ebp,%eax)
  506c09:      	fxch	%st(3)
  506c0b:      	fmulp	%st, %st(4)
  506c0d:      	fstps	0x694(%esp)
  506c14:      	fadds	0x10(%ebp,%eax)
  506c18:      	fxch	%st(2)
  506c1a:      	fadds	(%ebp,%eax)
  506c1e:      	fxch	%st(1)
  506c20:      	fstps	0x698(%esp)
  506c27:      	fxch	%st(1)
  506c29:      	fstps	0x69c(%esp)
  506c30:      	fstps	0x690(%esp)
  506c37:      	flds	0x6b8(%esp)
  506c3e:      	faddl	0x632380
  506c44:      	flds	0x690(%esp)
  506c4b:      	faddl	0x632380
  506c51:      	fxch	%st(1)
  506c53:      	fstpl	0x650(%esp)
  506c5a:      	fstpl	0x648(%esp)
  506c61:      	movl	0x650(%esp), %edx
  506c68:      	movl	0x648(%esp), %ebx
  506c6f:      	cmpl	%edx, %ebx
  506c71:      	je	0x50700b <.text+0x10600b>
  506c77:      	jl	0x506d19 <.text+0x105d19>
  506c7d:      	flds	0x690(%esp)
  506c84:      	fsubs	0x6b8(%esp)
  506c8b:      	flds	0x69c(%esp)
  506c92:      	fsubs	0x6c4(%esp)
  506c99:      	fxch	%st(1)
  506c9b:      	fdivrs	0x62c808
  506ca1:      	flds	0x698(%esp)
  506ca8:      	fsubs	0x6c0(%esp)
  506caf:      	fxch	%st(2)
  506cb1:      	fmul	%st(1), %st
  506cb3:      	flds	0x694(%esp)
  506cba:      	fsubs	0x6bc(%esp)
  506cc1:      	fxch	%st(3)
  506cc3:      	fmul	%st(2), %st
  506cc5:      	fxch	%st(1)
  506cc7:      	fstps	0x24(%esp)
  506ccb:      	fxch	%st(1)
  506ccd:      	fmulp	%st, %st(2)
  506ccf:      	fstps	0x20(%esp)
  506cd3:      	fildl	0x650(%esp)
  506cda:      	fxch	%st(1)
  506cdc:      	fstps	0x28(%esp)
  506ce0:      	fsubs	0x6b8(%esp)
  506ce7:      	flds	0x24(%esp)
  506ceb:      	flds	0x20(%esp)
  506cef:      	fmul	%st(2), %st
  506cf1:      	flds	0x28(%esp)
  506cf5:      	fmul	%st(3), %st
  506cf7:      	fxch	%st(1)
  506cf9:      	fadds	0x6c0(%esp)
  506d00:      	fxch	%st(3)
  506d02:      	fmulp	%st, %st(2)
  506d04:      	fadds	0x6bc(%esp)
  506d0b:      	fxch	%st(1)
  506d0d:      	fadds	0x6c4(%esp)
  506d14:      	jmp	0x506dc0 <.text+0x105dc0>
  506d19:      	movl	%ebx, 0x650(%esp)
  506d20:      	movl	%edx, %ebx
  506d22:      	movl	0x650(%esp), %edx
  506d29:      	flds	0x6b8(%esp)
  506d30:      	fsubs	0x690(%esp)
  506d37:      	flds	0x6c4(%esp)
  506d3e:      	fsubs	0x69c(%esp)
  506d45:      	fxch	%st(1)
  506d47:      	fdivrs	0x62c808
  506d4d:      	flds	0x6c0(%esp)
  506d54:      	fsubs	0x698(%esp)
  506d5b:      	fxch	%st(2)
  506d5d:      	fmul	%st(1), %st
  506d5f:      	flds	0x6bc(%esp)
  506d66:      	fsubs	0x694(%esp)
  506d6d:      	fxch	%st(3)
  506d6f:      	fmul	%st(2), %st
  506d71:      	fxch	%st(1)
  506d73:      	fstps	0x24(%esp)
  506d77:      	fxch	%st(1)
  506d79:      	fmulp	%st, %st(2)
  506d7b:      	fstps	0x20(%esp)
  506d7f:      	fildl	0x650(%esp)
  506d86:      	fxch	%st(1)
  506d88:      	fstps	0x28(%esp)
  506d8c:      	fsubs	0x690(%esp)
  506d93:      	flds	0x24(%esp)
  506d97:      	flds	0x20(%esp)
  506d9b:      	fmul	%st(2), %st
  506d9d:      	flds	0x28(%esp)
  506da1:      	fmul	%st(3), %st
  506da3:      	fxch	%st(1)
  506da5:      	fadds	0x698(%esp)
  506dac:      	fxch	%st(3)
  506dae:      	fmulp	%st, %st(2)
  506db0:      	fadds	0x694(%esp)
  506db7:      	fxch	%st(1)
  506db9:      	fadds	0x69c(%esp)
  506dc0:      	movl	0x18(%esp), %edi
  506dc4:      	subl	%edx, %ebx
  506dc6:      	addl	%edx, %edi
  506dc8:      	flds	0x20(%esp)
  506dcc:      	fmuls	0x62c814
  506dd2:      	flds	0x24(%esp)
  506dd6:      	fmuls	0x62c814
  506ddc:      	flds	0x28(%esp)
  506de0:      	fmuls	0x62c814
  506de6:      	fxch	%st(2)
  506de8:      	fstps	0x2c(%esp)
  506dec:      	fstps	0x30(%esp)
  506df0:      	fstps	0x34(%esp)
  506df4:      	fxch	%st(1)
  506df6:      	flds	0x62c80c
  506dfc:      	fdiv	%st(1), %st
  506dfe:      	fld	%st(2)
  506e00:      	fmul	%st(1), %st
  506e02:      	fld	%st(4)
  506e04:      	fmulp	%st, %st(2)
  506e06:      	faddl	0x632380
  506e0c:      	fxch	%st(1)
  506e0e:      	faddl	0x632380
  506e14:      	fxch	%st(2)
  506e16:      	fadds	0x34(%esp)
  506e1a:      	fxch	%st(1)
  506e1c:      	fstpl	0x680(%esp)
  506e23:      	fxch	%st(1)
  506e25:      	fstpl	0x678(%esp)
  506e2c:      	fxch	%st(2)
  506e2e:      	flds	0x62c80c
  506e34:      	fdiv	%st(3), %st
  506e36:      	decl	%ebx
  506e37:      	jmp	0x506f13 <.text+0x105f13>
  506e3c:      	flds	0x2c(%esp)
  506e40:      	faddp	%st, %st(2)
  506e42:      	flds	0x30(%esp)
  506e46:      	faddp	%st, %st(3)
  506e48:      	fld	%st(1)
  506e4a:      	fmul	%st(1), %st
  506e4c:      	flds	0x34(%esp)
  506e50:      	fxch	%st(2)
  506e52:      	fmul	%st(4), %st
  506e54:      	fxch	%st(2)
  506e56:      	faddp	%st, %st(5)
  506e58:      	faddl	0x632380
  506e5e:      	fxch	%st(1)
  506e60:      	faddl	0x632380
  506e66:      	fld	%st(4)
  506e68:      	fxch	%st(2)
  506e6a:      	fstpl	0x658(%esp)
  506e71:      	fstpl	0x668(%esp)
  506e78:      	fdivrs	0x62c80c
  506e7e:      	movl	0x680(%esp), %ebp
  506e85:      	movl	0x678(%esp), %esi
  506e8c:      	movl	0x668(%esp), %eax
  506e93:      	movl	0x658(%esp), %edx
  506e9a:      	subl	%ebp, %eax
  506e9c:      	subl	%esi, %edx
  506e9e:      	sarl	$0x4, %eax
  506ea1:      	movl	%ebx, 0x8(%esp)
  506ea5:      	sarl	$0x4, %edx
  506ea8:      	movl	%eax, 0x670(%esp)
  506eaf:      	movl	%edx, 0x660(%esp)
  506eb6:      	movl	$0x10, %ebx
  506ebb:      	movl	%ebp, %eax
  506ebd:      	movl	%esi, %edx
  506ebf:      	sarl	$0x10, %eax
  506ec2:      	movl	0x670(%esp), %ecx
  506ec9:      	sarl	$0x10, %edx
  506ecc:      	addl	%ecx, %ebp
  506ece:      	movl	0xcfdbd8(,%eax,4), %eax
  506ed5:      	movl	0x660(%esp), %ecx
  506edc:      	movb	(%eax,%edx), %dl
  506edf:      	addl	%ecx, %esi
  506ee1:      	movb	(%edi), %dh
  506ee3:      	incl	%edi
  506ee4:      	movb	0xd0e460(%edx), %al
  506eea:      	decl	%ebx
  506eeb:      	movb	%al, -0x1(%edi)
  506eee:      	jne	0x506ebb <.text+0x105ebb>
  506ef0:      	movl	0x8(%esp), %ebx
  506ef4:      	movl	0x658(%esp), %eax
  506efb:      	movl	0x668(%esp), %edx
  506f02:      	movl	%eax, 0x678(%esp)
  506f09:      	movl	%edx, 0x680(%esp)
  506f10:      	subl	$0x10, %ebx
  506f13:      	cmpl	$0x10, %ebx
  506f16:      	jge	0x506e3c <.text+0x105e3c>
  506f1c:      	cmpl	$0x0, %ebx
  506f1f:      	movl	0x680(%esp), %ebp
  506f26:      	movl	0x678(%esp), %esi
  506f2d:      	je	0x506feb <.text+0x105feb>
  506f33:      	fxch	%st(3)
  506f35:      	fsubs	0x34(%esp)
  506f39:      	flds	0x28(%esp)
  506f3d:      	fmuls	0x62c810(,%ebx,8)
  506f44:      	flds	0x20(%esp)
  506f48:      	fmuls	0x62c810(,%ebx,8)
  506f4f:      	flds	0x24(%esp)
  506f53:      	fmuls	0x62c810(,%ebx,8)
  506f5a:      	fxch	%st(2)
  506f5c:      	faddp	%st, %st(3)
  506f5e:      	faddp	%st, %st(3)
  506f60:      	faddp	%st, %st(3)
  506f62:      	fdivrs	0x62c80c
  506f68:      	fmul	%st, %st(1)
  506f6a:      	fildl	0x678(%esp)
  506f71:      	fxch	%st(1)
  506f73:      	fmul	%st(3), %st
  506f75:      	fildl	0x680(%esp)
  506f7c:      	fxch	%st(2)
  506f7e:      	fsubrp	%st, %st(3)
  506f80:      	fsubp	%st, %st(1)
  506f82:      	fxch	%st(1)
  506f84:      	fmuls	0x62c814(,%ebx,8)
  506f8b:      	fxch	%st(1)
  506f8d:      	fmuls	0x62c814(,%ebx,8)
  506f94:      	fxch	%st(1)
  506f96:      	faddl	0x632380
  506f9c:      	fxch	%st(1)
  506f9e:      	faddl	0x632380
  506fa4:      	fxch	%st(1)
  506fa6:      	fstl	0x660(%esp)
  506fad:      	fxch	%st(1)
  506faf:      	fstl	0x670(%esp)
  506fb6:      	movl	%ebp, %eax
  506fb8:      	movl	%esi, %edx
  506fba:      	sarl	$0x10, %eax
  506fbd:      	movl	0x670(%esp), %ecx
  506fc4:      	sarl	$0x10, %edx
  506fc7:      	addl	%ecx, %ebp
  506fc9:      	movl	0xcfdbd8(,%eax,4), %eax
  506fd0:      	movl	0x660(%esp), %ecx
  506fd7:      	movb	(%eax,%edx), %dl
  506fda:      	addl	%ecx, %esi
  506fdc:      	movb	(%edi), %dh
  506fde:      	incl	%edi
  506fdf:      	movb	0xd0e460(%edx), %al
  506fe5:      	decl	%ebx
  506fe6:      	movb	%al, -0x1(%edi)
  506fe9:      	jne	0x506fb6 <.text+0x105fb6>
  506feb:      	sarl	$0x10, %ebp
  506fee:      	xorl	%edx, %edx
  506ff0:      	sarl	$0x10, %esi
  506ff3:      	movb	(%edi), %dh
  506ff5:      	movl	0xcfdbd8(,%ebp,4), %eax
  506ffc:      	fcompp
  506ffe:      	movb	(%eax,%esi), %dl
  507001:      	fcompp
  507003:      	movb	0xd0e460(%edx), %al
  507009:      	movb	%al, (%edi)
  50700b:      	flds	0x694(%esp)
  507012:      	fadds	0x6ac(%esp)
  507019:      	flds	0x69c(%esp)
  507020:      	fadds	0x6a4(%esp)
  507027:      	flds	0x698(%esp)
  50702e:      	fadds	0x6a0(%esp)
  507035:      	flds	0x690(%esp)
  50703c:      	fadds	0x6a8(%esp)
  507043:      	fxch	%st(3)
  507045:      	fstps	0x694(%esp)
  50704c:      	fstps	0x698(%esp)
  507053:      	fstps	0x69c(%esp)
  50705a:      	fstps	0x690(%esp)
  507061:      	flds	0x6bc(%esp)
  507068:      	fadds	0x6d4(%esp)
  50706f:      	flds	0x6c4(%esp)
  507076:      	fadds	0x6cc(%esp)
  50707d:      	flds	0x6c0(%esp)
  507084:      	fadds	0x6c8(%esp)
  50708b:      	flds	0x6b8(%esp)
  507092:      	fadds	0x6d0(%esp)
  507099:      	fxch	%st(3)
  50709b:      	fstps	0x6bc(%esp)
  5070a2:      	fstps	0x6c0(%esp)
  5070a9:      	fstps	0x6c4(%esp)
  5070b0:      	fstps	0x6b8(%esp)
  5070b7:      	movl	0x18(%esp), %esi
  5070bb:      	movl	0xc(%esp), %eax
  5070bf:      	movl	(%esp), %ebp
  5070c2:      	addl	%eax, %esi
  5070c4:      	movl	0x4(%esp), %edi
  5070c8:      	movl	%esi, 0x18(%esp)
  5070cc:      	incl	%edi
  5070cd:      	jmp	0x506a13 <.text+0x105a13>
  5070d2:      	leal	0x6d8(%esp), %ecx
  5070d9:      	calll	0x50552a <.text+0x10452a>
  5070de:      	addl	$0x7d8, %esp            # imm = 0x7D8
  5070e4:      	popl	%ebp
  5070e5:      	popl	%edi
  5070e6:      	popl	%esi
  5070e7:      	popl	%ebx
  5070e8:      	popl	%ebp
  5070e9:      	retl
