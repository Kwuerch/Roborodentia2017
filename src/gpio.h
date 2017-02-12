#ifndef GPIO_H_
#define GPIO_H_

void GPIO_INIT( GPIO_TypeDef* GPIOx, uint16_t pin);

void setPin(GPIO_TypeDef* GPIOx, uint16_t pin);
void resetPin(GPIO_TypeDef* GPIOx, uint16_t pin);
void togglePin(GPIO_TypeDef* GPIOx, uint16_t pin);

void setLedsFromInput(uint16_t input);

#endif
