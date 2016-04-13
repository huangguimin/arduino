int led_pin = 8;               // 定义引脚13为LED引脚  
void setup()  
{  
  pinMode(led_pin, OUTPUT);     // 设置LED引脚为输出模式  
}  
void loop()  
{  
  digitalWrite(led_pin, HIGH);      // 设置引脚为高电平，LED点亮  
  delay(1000);  // 等待1s  
  digitalWrite(led_pin, LOW);       // 设置引脚为低电平，LED熄灭  
  delay(1000);  // 等待1s  
} 
