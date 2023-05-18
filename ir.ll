; ModuleID = 'output'
source_filename = "output"
target datalayout = "e-m:e-p:64:64-i64:64-i128:128-n64-S128"
target triple = "riscv64-unknown-linux-gnu"

@x = global i32 0
@y = external global i32
@z = global i32 1
