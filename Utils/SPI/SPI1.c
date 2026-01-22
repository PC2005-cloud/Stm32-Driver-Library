#include "main.h"

/* 引脚定义 */
#define SPI1_CS_PIN      4
#define SPI1_MISO_PIN    6    // DO
#define SPI1_SCK_PIN     5    // SLK
#define SPI1_MOSI_PIN    7    // DI


/* 快速GPIO操作宏 */
#define SPI1_GPIO_SET(port, pin, value) \
    ((value) ? ((port)->BSRR = (1U << (pin))) : ((port)->BRR = (1U << (pin))))

#define SPI1_GPIO_GET(port, pin) \
    (((port)->IDR >> (pin)) & 0x01)

/* 软件控制引脚函数 */
void SPI1_W_SS(uint8_t BitValue)
{
    SPI1_GPIO_SET(GPIOA, SPI1_CS_PIN, BitValue);
}

void SPI1_W_SCK(uint8_t BitValue)
{
    SPI1_GPIO_SET(GPIOA, SPI1_SCK_PIN, BitValue);
}

void SPI1_W_MOSI(uint8_t BitValue)
{
    SPI1_GPIO_SET(GPIOA, SPI1_MOSI_PIN, BitValue);
}

uint8_t SPI1_R_MISO(void)
{
    return SPI1_GPIO_GET(GPIOA, SPI1_MISO_PIN);
}

void SPI1_Init(void)
{
    /* 1. 使能GPIOA和SPI1时钟 */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_SPI1EN;

    /* 2. 配置CS引脚(PA4)为推挽输出 */
    /* CRL寄存器控制引脚0-7，每个引脚占4位 */
    uint32_t temp = GPIOA->CRL;
    temp &= ~(0xF << (SPI1_CS_PIN * 4));       // 清除原配置
    temp |= (0x1 << (SPI1_CS_PIN * 4));        // 通用推挽输出，速度10MHz
    GPIOA->CRL = temp;

    /* 3. 配置SPI功能引脚为复用推挽输出 */
    /* SCK(PA5), MOSI(PA7) */
    temp = GPIOA->CRL;
    temp &= ~(0xF << (SPI1_SCK_PIN * 4));      // 清除SCK配置
    temp |= (0xB << (SPI1_SCK_PIN * 4));       // 复用推挽输出，最大速度50MHz

    temp &= ~(0xF << (SPI1_MOSI_PIN * 4));     // 清除MOSI配置
    temp |= (0xB << (SPI1_MOSI_PIN * 4));      // 复用推挽输出，最大速度50MHz
    GPIOA->CRL = temp;

    /* 4. 配置MISO(PA6)为浮空输入 */
    temp = GPIOA->CRL;
    temp &= ~(0xF << (SPI1_MISO_PIN * 4));     // 清除MISO配置
    temp |= (0x4 << (SPI1_MISO_PIN * 4));      // 浮空输入模式
    GPIOA->CRL = temp;

    /* 5. 配置硬件SPI1 */
    SPI1->CR1 = 0;                            // 先清除所有配置

    /* 配置SPI参数:
     * CPOL=0: 时钟低电平空闲
     * CPHA=0: 第一个时钟边沿采样
     * MSTR=1: 主模式
     * BR[2:0]=001: fPCLK/4 (如果PCLK=72MHz, SPI=18MHz)
     * SPE=0: 先不使能SPI
     * LSBFIRST=0: MSB先发送
     * SSM=1, SSI=1: 软件NSS管理
     * DFF=0: 8位数据格式
     */
    SPI1->CR1 |= SPI_CR1_MSTR;                // 主模式
    SPI1->CR1 |= SPI_CR1_BR_0;                // 预分频器/4
    SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;   // 软件NSS管理

    /* 6. 使能SPI */
    SPI1->CR1 |= SPI_CR1_SPE;

    /* 7. 设置CS默认高电平 */
    SPI1_W_SS(1);
}

void SPI1_Start(void)
{
    SPI1_W_SS(0);                // 拉低SS，开始时序
}

void SPI1_Stop(void)
{
    SPI1_W_SS(1);                // 拉高SS，终止时序
}

/* SPI状态检查 */
static uint8_t SPI1_CheckFlag(uint32_t flag)
{
    return (SPI1->SR & flag) ? 1 : 0;
}

/* 等待发送完成 */
static void SPI1_WaitTXE(void)
{
    while(!SPI1_CheckFlag(SPI_SR_TXE));
}

/* 等待接收完成 */
static void SPI1_WaitRXNE(void)
{
    while(!SPI1_CheckFlag(SPI_SR_RXNE));
}

/* 交换1个字节 - 使用寄存器直接操作 */
uint8_t SPI1_SwapByte(uint8_t ByteSend)
{
    uint8_t ByteReceive = 0;

    /* 等待发送缓冲区空 */
    SPI1_WaitTXE();

    /* 写入数据到数据寄存器，开始发送 */
    SPI1->DR = ByteSend;

    /* 等待接收完成 */
    SPI1_WaitRXNE();

    /* 读取接收到的数据 */
    ByteReceive = (uint8_t)SPI1->DR;

    return ByteReceive;
}

/* 使用硬件SPI发送1个字节并控制CS */
void SPI1_SwapByte1(uint8_t ByteSend)
{
    SPI1_Start();
    SPI1_SwapByte(ByteSend);
    SPI1_Stop();
}

/* 使用硬件SPI发送2个字节并控制CS */
void SPI1_SwapByte2(uint16_t ByteSend)
{
    SPI1_Start();

    /* 发送高字节 */
    SPI1_SwapByte((uint8_t) (ByteSend >> 8));

    /* 发送低字节 */
    SPI1_SwapByte((uint8_t) ByteSend);

    SPI1_Stop();
}

/* 使用硬件SPI发送多个字节 */
void SPI2_WriteBytes(uint8_t *data, uint16_t length)
{
    SPI1_Start();

    for(uint16_t i = 0; i < length; i++)
    {
        SPI1_SwapByte(data[i]);
    }

    SPI1_Stop();
}

/* 使用硬件SPI接收多个字节 */
void SPI1_ReadBytes(uint8_t *data, uint16_t length)
{
    SPI1_Start();

    for(uint16_t i = 0; i < length; i++)
    {
        data[i] = SPI1_SwapByte(0xFF);  // 发送哑元数据以接收
    }

    SPI1_Stop();
}

/* 软件模拟SPI函数（备用） */
uint8_t SPI1_SwapByte_Soft(uint8_t ByteSend)
{
    uint8_t i, ByteReceive = 0;

    SPI1_Start();

    for(i = 0; i < 8; i++)
    {
        /* 设置时钟低 */
        SPI1_W_SCK(0);

        /* 设置MOSI输出数据位 */
        SPI1_W_MOSI((ByteSend & 0x80) >> 7);
        ByteSend <<= 1;



        /* 时钟上升沿，从设备采样 */
        SPI1_W_SCK(1);

        /* 读取MISO数据位 */
        ByteReceive <<= 1;
        ByteReceive |= SPI1_R_MISO();


    }

    SPI1_Stop();
    return ByteReceive;
}