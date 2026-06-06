#define LED_PIN 2

//setting up registers
#define GPIO_OUT_REG *((volatile uint32_t*)0x3FF44004)
#define GPIO_ENABLE_REG *((volatile uint32_t*)0x3FF44020)

void setup() {
  // put your setup code here, to run once:
  GPIO_ENABLE_REG |=(1<<LED_PIN);
}

void loop() {
  // put your main code here, to run repeatedly:
  GPIO_OUT_REG |= (1<<LED_PIN);
  delay(1000);
  GPIO_OUT_REG &=~ (1<<LED_PIN);
  delay(1000);

}
