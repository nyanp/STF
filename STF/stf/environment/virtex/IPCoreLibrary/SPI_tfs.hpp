#ifndef SPI_TFS_HPP_
#define SPI_TFS_HPP_

template<typename AC>
SPI<AC>::SPI(unsigned int base_addr,
	SPIParams::OPERATION_MODE mode, SPIParams::DUPLEX_MODE d_mode,
	SPIParams::MANUAL_SLAVE_SELECT_ASSERTION mssa, SPIParams::CLOCK_POLARITY polar,
	SPIParams::CLOCK_PHASE phase, SPIParams::TRANSMISSION_ORDER order,
	SPIParams::LOOPBACK_MODE loopback) : 
	SRR_(*reinterpret_cast<volatile unsigned int*>(base_addr+SRR_OFFSET_)),
	SPICR_(*reinterpret_cast<volatile unsigned int*>(base_addr+SPICR_OFFSET_)),
	SPISR_(*reinterpret_cast<volatile unsigned int*>(base_addr+SPISR_OFFSET_)),
	SPIDTR_(*reinterpret_cast<volatile unsigned int*>(base_addr+SPIDTR_OFFSET_)),
	SPIDRR_(*reinterpret_cast<volatile unsigned int*>(base_addr+SPIDRR_OFFSET_)),
	SPISSR_(*reinterpret_cast<volatile unsigned int*>(base_addr+SPISSR_OFFSET_)),
	SPITFOR_(*reinterpret_cast<volatile unsigned int*>(base_addr+SPITFOR_OFFSET_)),
	SPIRFOR_(*reinterpret_cast<volatile unsigned int*>(base_addr+SPIRFOR_OFFSET_)),
	DGIER_(*reinterpret_cast<volatile unsigned int*>(base_addr+DGIER_OFFSET_)),
	IPISR_(*reinterpret_cast<volatile unsigned int*>(base_addr+IPISR_OFFSET_)),
	IPIER_(*reinterpret_cast<volatile unsigned int*>(base_addr+IPIER_OFFSET_)),
	d_mode_(d_mode)
{
	reset();

	switch(mode)
	{
	case SPIParams::MASTER_MODE:
		enable_master_mode_();
		enable_master_transaction_();
		break;
	case SPIParams::SLAVE_MODE:
		enable_slave_mode_();
		break;
	}
	
	switch(mssa)
	{
	case SPIParams::ENABLE_MSSA:
		enable_manual_slave_select_assertion_();
		break;
	case SPIParams::DISABLE_MSSA:
		disable_manual_slave_select_assertion_();
		break;
	}
	
	switch(polar)
	{
	case SPIParams::CLK_IDLE_HIGH:
		enable_active_low_();
		break;
	case SPIParams::CLK_IDLE_LOW:
		enable_active_high_();
		break;
	}
			
	switch(phase)
	{
	case SPIParams::CLK_PHASE_FIRST:
		enable_clock_phase_first_();
		break;
	case SPIParams::CLK_PHASE_SECOND:
		enable_clock_phase_second_();
		break;
	}
	
	switch(order)
	{
	case SPIParams::MSB_FIRST:
		enable_msb_first_();
		break;
	case SPIParams::LSB_FIRST:
		enable_lsb_first_();
		break;
	}
	
	switch(loopback)
	{
	case SPIParams::ENABLE_LOOPBACK:
		enable_loopback_();
		break;
	case SPIParams::DISABLE_LOOPBACK:
		disable_loopback_();
		break;
	}
	
	reset_tx_fifo();
	reset_rx_fifo();
	enable_spi_();
}

template<typename AC>
SPI<AC>::~SPI()
{
	disable_spi_();
}

template<typename AC>
int SPI<AC>::putchar(int c)
{
	AccessControl<AC> ac_obj;
	
	//Tx FIFOが満杯の場合、データを送信できずEOFを返す。
	if(is_tx_fifo_full())
	{
		return EOF;
	}
	
	// データ送信
	SPIDTR_ = c;
	
	//半2重通信の場合、送信と同時に受信される不要なデータを読み飛ばす。
	if(d_mode_ == SPIParams::HALF_DUPLEX)
	{
		while(is_rx_fifo_empty()); 
		int c = SPIDRR_; //データの読み飛ばし。
		(void)c;
	}

	return c;
}

template<typename AC>
int SPI<AC>::getchar()
{
	AccessControl<AC> ac_obj;
	
	// 半2重通信の場合ダミーデータを送出。
	if(d_mode_ == SPIParams::HALF_DUPLEX)
	{
		while(is_tx_fifo_full());
		SPIDTR_ = 0xff; //ダミーデータ
		while(!is_tx_fifo_empty()); //送信が完全に完了するまで待機。
	}
	
	// Rx FIFOが空の場合、データが無く、EOFを返す。
	if(is_rx_fifo_empty())
	{
		return EOF;
	}
	
	return SPIDRR_;
}

template<typename AC>
unsigned int SPI<AC>::putint(unsigned int c)
{
	AccessControl<AC> ac_obj;
	
	//Tx FIFOが満杯の場合、データを送信できずEOFを返す。
	if(is_tx_fifo_full())
	{
		return EOF;
	}
	
	// データ送信
	SPIDTR_ = c;
	//Masterの場合、RXFIFOへ帰ってくるデータの処理
	if(SPICR_ & SPICR_MASTER_)
	{
	    //半2重通信の場合、送信と同時に受信される不要なデータを読み飛ばす。
		if(d_mode_ == SPIParams::HALF_DUPLEX)
		{
			while(is_rx_fifo_empty()); 
			unsigned int c = SPIDRR_; //データの読み飛ばし。
			(void)c;
		}
		else
		{	//全2重通信の場合は返り値は受信データ
			while(is_rx_fifo_empty());	
			unsigned int r = SPIDRR_;
			return r;
		}
	} 
	return c;
}

template<typename AC>
unsigned int SPI<AC>::getint()
{
	AccessControl<AC> ac_obj;
		
	// 半2重通信でMasterの場合ダミーデータを送出。
	if(d_mode_ == SPIParams::HALF_DUPLEX && (SPICR_ & SPICR_MASTER_))
	{
		while(is_tx_fifo_full());
		SPIDTR_ = 0xffffffff; //ダミーデータ
		while(!is_tx_fifo_empty()); //送信が完全に完了するまで待機。
	}
	
	// Rx FIFOが空の場合、データが無く、EOFを返す。
	if(is_rx_fifo_empty())
	{
	return EOF;
	}
	
	return SPIDRR_;
}

#endif /*SPI_TFS_HPP_*/
