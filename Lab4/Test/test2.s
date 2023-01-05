.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
read:
  li $v0, 4
  la $a0, _prompt
  syscall
  li $v0, 5
  syscall
  jr $ra

write:
  li $v0, 1
  syscall
  li $v0, 4
  la $a0, _ret
  syscall
  move $v0, $0
  jr $ra

fact:
  move $fp, $sp
  addi $sp, $sp, 0


  lw $t0, -4($fp)
  li $t1, 1
  beq $t0, $t1, label0

  j label1

  label0:

  lw $t0, -4($fp)
  move $v0, $t0
  jr $ra

  j label2

  label1:

  lw $t1, -8($fp)
  li $t2, 1
  sub $t0, $t1, $t2
  sw $t0, -4($fp)

  lw $t0, -4($fp)
  addi $sp, $sp, -4
  sw $t0, 0($sp)

  addi $sp, $sp, -8
  sw $fp, 0($sp)
  sw $ra, 4($sp)
  jal fact
  move $sp, $fp
  lw $ra, 4($sp)
  lw $fp, 0($sp)
  addi $sp, $sp, 12
  move $t0, $v0
  sw $t0, -4($fp)

  lw $t1, -8($fp)
  lw $t2, -12($fp)
  mul $t0, $t1, $t2
  sw $t0, -4($fp)

  lw $t0, -4($fp)
  move $v0, $t0
  jr $ra

  label2:

main:
  move $fp, $sp
  addi $sp, $sp, 0

  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  move $t0, $v0
  sw $t0, -4($fp)

  lw $t1, -8($fp)
  move $t0, $t1
  sw $t0, -4($fp)

  lw $t0, -4($fp)
  li $t1, 1
  bgt $t0, $t1, label3

  j label4

  label3:

  lw $t0, -4($fp)
  addi $sp, $sp, -4
  sw $t0, 0($sp)

  addi $sp, $sp, -8
  sw $fp, 0($sp)
  sw $ra, 4($sp)
  jal fact
  move $sp, $fp
  lw $ra, 4($sp)
  lw $fp, 0($sp)
  addi $sp, $sp, 12
  move $t0, $v0
  sw $t0, -4($fp)

  lw $t1, -8($fp)
  move $t0, $t1
  sw $t0, -4($fp)

  j label5

  label4:

  li $t1, 1
  move $t0, $t1
  sw $t0, -4($fp)

  label5:

  lw $t0, -4($fp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4

  li $t0, 0
  move $v0, $t0
  jr $ra

