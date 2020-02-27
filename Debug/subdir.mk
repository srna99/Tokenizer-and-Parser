################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Analyzer.c \
../Givens.c \
../Parser.c \
../Tokenizer.c 

OBJS += \
./Analyzer.o \
./Givens.o \
./Parser.o \
./Tokenizer.o 

C_DEPS += \
./Analyzer.d \
./Givens.d \
./Parser.d \
./Tokenizer.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


