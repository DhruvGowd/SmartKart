################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/SPILCD.c \
../src/adc.c \
../src/main.c \
../src/syscalls.c \
../src/system_stm32f0xx.c \
../src/table.c \
../src/usartf0.c 

OBJS += \
./src/SPILCD.o \
./src/adc.o \
./src/main.o \
./src/syscalls.o \
./src/system_stm32f0xx.o \
./src/table.o \
./src/usartf0.o 

C_DEPS += \
./src/SPILCD.d \
./src/adc.d \
./src/main.d \
./src/syscalls.d \
./src/system_stm32f0xx.d \
./src/table.d \
./src/usartf0.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32F0 -DSTM32F051R8Tx -DSTM32F0DISCOVERY -DDEBUG -DSTM32F051 -DUSE_STDPERIPH_DRIVER -I"C:/Users/DhruvG/Documents/Senior Design/SmartKart/Utilities" -I"C:/Users/DhruvG/Documents/Senior Design/SmartKart/StdPeriph_Driver/inc" -I"C:/Users/DhruvG/Documents/Senior Design/SmartKart/inc" -I"C:/Users/DhruvG/Documents/Senior Design/SmartKart/CMSIS/device" -I"C:/Users/DhruvG/Documents/Senior Design/SmartKart/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


