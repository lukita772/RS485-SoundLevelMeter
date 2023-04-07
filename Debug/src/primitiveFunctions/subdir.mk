################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/primitiveFunctions/adc_primitive.c \
../src/primitiveFunctions/lcd_primitive.c \
../src/primitiveFunctions/timeMachine.c \
../src/primitiveFunctions/uart_primitive.c 

OBJS += \
./src/primitiveFunctions/adc_primitive.o \
./src/primitiveFunctions/lcd_primitive.o \
./src/primitiveFunctions/timeMachine.o \
./src/primitiveFunctions/uart_primitive.o 

C_DEPS += \
./src/primitiveFunctions/adc_primitive.d \
./src/primitiveFunctions/lcd_primitive.d \
./src/primitiveFunctions/timeMachine.d \
./src/primitiveFunctions/uart_primitive.d 


# Each subdirectory must supply rules for building sources it contributes
src/primitiveFunctions/%.o: ../src/primitiveFunctions/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


