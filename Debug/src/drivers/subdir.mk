################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/drivers/adc_driver.c \
../src/drivers/antiBounce_driver.c \
../src/drivers/gpio.c \
../src/drivers/initializeSystem.c \
../src/drivers/lcd_driver.c \
../src/drivers/oscilator.c \
../src/drivers/pinConfig.c \
../src/drivers/sysTick_Handler.c \
../src/drivers/uart_driver.c 

OBJS += \
./src/drivers/adc_driver.o \
./src/drivers/antiBounce_driver.o \
./src/drivers/gpio.o \
./src/drivers/initializeSystem.o \
./src/drivers/lcd_driver.o \
./src/drivers/oscilator.o \
./src/drivers/pinConfig.o \
./src/drivers/sysTick_Handler.o \
./src/drivers/uart_driver.o 

C_DEPS += \
./src/drivers/adc_driver.d \
./src/drivers/antiBounce_driver.d \
./src/drivers/gpio.d \
./src/drivers/initializeSystem.d \
./src/drivers/lcd_driver.d \
./src/drivers/oscilator.d \
./src/drivers/pinConfig.d \
./src/drivers/sysTick_Handler.d \
./src/drivers/uart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
src/drivers/%.o: ../src/drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


