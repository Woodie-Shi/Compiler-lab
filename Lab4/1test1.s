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

main:
  move $fp, $sp
  addi $sp, $sp, 0

  li $t1, 0
  move $t0, $t1
  sw $t0, -4($fp)

  li $t1, 1
  move $t0, $t1
  sw $t0, -4($fp)

  li $t1, 0
  move $t0, $t1
  sw $t0, -4($fp)

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

  label0:

  lw $t0, -4($fp)
  lw $t1, -8($fp)
  blt $t0, $t1, label1

  j label2

  label1:

  lw $t1, -8($fp)
  lw $t2, -12($fp)
  add $t0, $t1, $t2
  sw $t0, -4($fp)

  lw $t1, -8($fp)
  move $t0, $t1
  sw $t0, -4($fp)

  lw $t0, -4($fp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4

  lw $t1, -8($fp)
  move $t0, $t1
  sw $t0, -4($fp)

  lw $t1, -8($fp)
  move $t0, $t1
  sw $t0, -4($fp)

  lw $t1, -8($fp)
  li $t2, 1
  add $t0, $t1, $t2
  sw $t0, -4($fp)

  lw $t1, -8($fp)
  move $t0, $t1
  sw $t0, -4($fp)

  j label0

  label2:

  li $t0, 0
  move $v0, $t0
  jr $ra

