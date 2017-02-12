#ifndef GPIO_H_
#define GPIO_H_

void GPIO_INIT_A(uint16_t pin);
void GPIO_INIT_B(uint16_t pin);
void GPIO_INIT_E(uint16_t pin);

void setPin(GPIO_TypeDef* gpio_port, uint16_t pin);
void resetPin(GPIO_TypeDef* gpio_port, uint16_t pin);
void togglePin(GPIO_TypeDef* gpio_port, uint16_t pin);

void setLedsFromInput(uint16_t input);

#endif
