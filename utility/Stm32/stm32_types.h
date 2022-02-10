#pragma once

typedef enum
{
	TxReady,
	RxReady,
	TransferComplete
}SpiNotify_t;

typedef enum {
    TxRxTransfer = 0,
    TxOnly,
    RxOnly
} TransferType_t;
