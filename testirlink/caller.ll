; ModuleID = 'caller'
source_filename = "caller"

@str = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

declare i32 @printf(i8*, ...)

define i32 @main() {
start:
  %add_result = call i32 @add(i32 10, i32 25)
  %0 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @str, i32 0, i32 0), i32 %add_result)
  ret i32 %add_result
}

; External declaration of the add function
declare i32 @add(i32, i32)
