
// 定义GPIOA、GPIOB、GPIOC的基地址
#define GPIOA_BASE 0x40010800
#define GPIOB_BASE 0x40010C00 
#define GPIOC_BASE 0x40011000

// 定义RCC_APB2ENR寄存器的地址，用于开启GPIO时钟
#define RCC_APB2ENR (*(unsigned int *)0x40021018)

// 定义GPIOA、GPIOB、GPIOC的CRL和CRH寄存器的地址，用于配置GPIO模式
#define GPIOA_CRL (*(unsigned int *)0x40010800)
#define GPIOB_CRL (*(unsigned int *)0x40010C00)  
#define GPIOC_CRL (*(unsigned int *)0x40011000) 

// 定义GPIOA、GPIOB、GPIOC的ODR寄存器的地址，用于设置GPIO输出数据
#define GPIOA_ODR (*(unsigned int *)0x4001080C)
#define GPIOB_ODR (*(unsigned int *)0x40010C0C)
#define GPIOC_ODR (*(unsigned int *)0x4001100C)	

// 延时函数声明
void Delay_ms(volatile  unsigned  int);
// 点亮A端口LED的函数声明
void A_LED_LIGHT(void);
// 点亮B端口LED的函数声明
void B_LED_LIGHT(void);
// 点亮C端口LED的函数声明
void C_LED_LIGHT(void);

// 延时函数实现
// 使用volatile关键字防止编译器优化
void Delay_ms( volatile  unsigned  int  t)
{
     unsigned  int  i;
     // 外层循环控制延时的时间
     while(t--)
         // 内层循环用于消耗时间，实现延时
         for (i=0;i<800;i++);
}
 
// 点亮A端口LED的函数实现
void A_LED_LIGHT(){
	// 将PA1设置为低电平，点亮LED
	GPIOA_ODR=0x0<<1;		
	// 延时1000ms
	Delay_ms(1000);
	// 将PA1设置为高电平，熄灭LED
	GPIOA_ODR=0x1<<1;		
}

// 点亮B端口LED的函数实现
void B_LED_LIGHT(){
	// 将PB1设置为低电平，点亮LED
	GPIOB_ODR=0x0<<1;		
	// 延时1000ms
	Delay_ms(1000);
	// 将PB1设置为高电平，熄灭LED
	GPIOB_ODR=0x1<<1;		
}

// 点亮C端口LED的函数实现
void C_LED_LIGHT(){
	// 将PC13设置为低电平，点亮LED	
	GPIOC_ODR=0x0<<13;		
	// 延时1000ms
	Delay_ms(1000);
	// 将PC13设置为高电平，熄灭LED
	GPIOC_ODR=0x1<<13;		
}

// 主函数
int main(){
	int j=100;
	
	// 开启GPIOA、GPIOB、GPIOC的时钟
	RCC_APB2ENR |= (1<<2); // 开启 GPIOA 时钟
	RCC_APB2ENR |= (1<<3); // 开启 GPIOB 时钟
	RCC_APB2ENR |= (1<<4); // 开启 GPIOC 时钟	
	
	// 设置GPIOA的PA1为推挽输出
	GPIOA_CRL &= 0xfffff0ff; // 将CRL寄存器的PA0-7位清零		
	GPIOA_CRL|=0x00000200; // 设置PA1为推挽输出
	
	// 设置GPIOB的PB1为推挽输出
	GPIOB_CRL &= 0xfffffff0;	// 将CRL寄存器的PB0-7位清零		
	GPIOB_CRL|=0x00000002;  // 设置PB1为推挽输出
   
	// 设置GPIOC的PC13为推挽输出
	GPIOC_CRL &= 0xffff1fff; // 将CRL寄存器的PC12-15位清零		
	GPIOC_CRL|=0x00008000;  // 设置PC13为推挽输出 
	
	// 初始化，将三个LED设置为高电平（熄灭）
	GPIOA_ODR |= (1<<1);  
	GPIOB_ODR |= (1<<1); 
	GPIOC_ODR |= (1<<13); 
	
	// 循环100次，依次点亮三个LED
	while(j--){
		A_LED_LIGHT();

		B_LED_LIGHT();
 
		C_LED_LIGHT();
	}
	
	// 程序结束
	return 0;
}
